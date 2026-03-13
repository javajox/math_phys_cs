using Test
using CUDA
using VectorOps

@testset "gpu_scalar_vector_mul_to_cpu" begin
    if !CUDA.functional()
        @test_skip VectorOps.gpu_scalar_vector_mul_to_cpu(2.0f0, Float32[1, 2, 3]) == Float32[2, 4, 6]
    else
        @testset "basic multiplication" begin
            k = 2.0f0
            u = Float32[1, 2, 3]

            result = VectorOps.gpu_scalar_vector_mul_to_cpu(k, u)

            @test result == Float32[2, 4, 6]
            @test result isa Vector{Float32}
        end

        @testset "zero scalar" begin
            k = 0.0f0
            u = Float32[5, 6, 7]

            result = VectorOps.gpu_scalar_vector_mul_to_cpu(k, u)

            @test result == Float32[0, 0, 0]
        end

        @testset "negative scalar" begin
            k = -3.0f0
            u = Float32[1, 2, 3]

            result = VectorOps.gpu_scalar_vector_mul_to_cpu(k, u)

            @test result == Float32[-3, -6, -9]
        end

        @testset "empty vector" begin
            k = 4.0f0
            u = Float32[]

            result = VectorOps.gpu_scalar_vector_mul_to_cpu(k, u)

            @test result == Float32[]
        end
    end
end
