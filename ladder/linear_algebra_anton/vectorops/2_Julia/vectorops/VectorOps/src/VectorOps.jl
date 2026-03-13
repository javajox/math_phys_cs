module VectorOps

using CUDA

export gpu_vector_add, gpu_vector_add_to_cpu
export gpu_scalar_vector_mul, gpu_scalar_vector_mul_to_cpu
export gpu_euclidean_norm
export gpu_euclidean_distance

function _ensure_cuda()
    CUDA.functional() || error(
        "CUDA is not functional on this system. Check your NVIDIA driver and CUDA.jl setup."
    )
    return nothing
end

function _to_cu(x::AbstractVector)
    return x isa CUDA.CuVector ? x : CuArray(x)
end

"""
Add two vectors on the GPU and return the result as a 'CuVector'.
If 'a' and 'b' are normal CPU vectors, they are copied to the GPU first
"""
function gpu_vector_add(a::AbstractVector, b::AbstractVector)
    length(a) == length(b) || throw(DimensionMismatch("vectors must have the same length"))
    _ensure_cuda()

    d_a = _to_cu(a)
    d_b = _to_cu(b)

    d_c = d_a .+ d_b

    return d_c
end

"""
Add two vectors on GPU and return the result as normal CPU 'Vector'.
"""
function gpu_vector_add_to_cpu(a::AbstractVector, b::AbstractVector)
    return Array(gpu_vector_add(a, b))
end

"""
    gpu_scalar_vector_mul(k, u)

Multiply scalar `k` by vector `u` on the GPU and return the result as a `CuVector`.
"""
function gpu_scalar_vector_mul(k::Number, u::AbstractVector)
    _ensure_cuda()

    d_u = _to_cu(u)

    return k .* d_u
end

"""
    gpu_scalar_vector_mul_to_cpu(k, u)

Multiply scalar `k` by vector `u` on the GPU and return the result as a CPU `Vector`.
"""
function gpu_scalar_vector_mul_to_cpu(k::Number, u::AbstractVector)
    return Array(gpu_scalar_vector_mul(k, u))
end

"""
    gpu_euclidean_norm(u)

Compute the Euclidean norm of vector `u` using the GPU.
The vector is copied to the GPU if needed.
Returns a scalar Julia number.
"""
function gpu_euclidean_norm(u::AbstractVector)
   _ensure_cuda()
  d_u = _to_cu(u)
  return sqrt(mapreduce(abs2, +, d_u))
end

"""
    gpu_euclidean_distance(u, v)

Compute the Euclidean distance between vectors `u` and `v` using the GPU.
Returns a scalar Julia number.
"""
function gpu_euclidean_distance(u::AbstractVector, v::AbstractVector)
    length(u) == length(v) || throw(DimensionMismatch("vectors must have the same length"))
    _ensure_cuda()
    d_u = _to_cu(u)
    d_v = _to_cu(v)
    return sqrt(mapreduce(abs2, +, d_u .- d_v))
end

end # module VectorOps
