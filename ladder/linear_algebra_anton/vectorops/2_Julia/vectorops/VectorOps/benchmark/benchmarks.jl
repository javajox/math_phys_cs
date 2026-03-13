using BenchmarkTools
using CUDA
using VectorOps
using Random

CUDA.functional() || error("CUDA is not functional in the benchmark environment")

Random.seed!(1234)

const SUITE = BenchmarkGroup()
const SIZES = [1_024, 1_048_576]

for n in SIZES
    a = rand(Float32, n)
    b = rand(Float32, n)
    k = 2.5f0

    g = SUITE["n=$n"] = BenchmarkGroup()

    g["gpu_vector_add"] =
        @benchmarkable begin
            CUDA.@sync VectorOps.gpu_vector_add($a, $b)
        end evals = 1

    g["gpu_vector_add_to_cpu"] =
        @benchmarkable begin
            CUDA.@sync VectorOps.gpu_vector_add_to_cpu($a, $b)
        end evals = 1

    g["gpu_scalar_vector_mul"] =
        @benchmarkable begin
            CUDA.@sync VectorOps.gpu_scalar_vector_mul($k, $a)
        end evals = 1

    g["gpu_scalar_vector_mul_to_cpu"] =
        @benchmarkable begin
            CUDA.@sync VectorOps.gpu_scalar_vector_mul_to_cpu($k, $a)
        end evals = 1

    g["gpu_euclidean_norm"] =
        @benchmarkable begin
            CUDA.@sync VectorOps.gpu_euclidean_norm($a)
        end evals = 1

    g["gpu_euclidean_distance"] =
        @benchmarkable begin
            CUDA.@sync VectorOps.gpu_euclidean_distance($a, $b)
        end evals = 1
end
