using Test
using CUDA
using VectorOps

@testset "gpu_euclidean_norm" begin
    if !CUDA.functional()
        @test_skip VectorOps.gpu_euclidean_norm(Float32[3, 4]) ≈ 5.0f0
    else
        @testset "basic case" begin
            u = Float32[3, 4]
            result = VectorOps.gpu_euclidean_norm(u)

            @test result ≈ 5.0f0
            @test result isa Float32
        end

        @testset "zero vector" begin
            u = Float32[0, 0, 0]
            result = VectorOps.gpu_euclidean_norm(u)

            @test result ≈ 0.0f0
        end

        @testset "single element" begin
            u = Float32[7]
            result = VectorOps.gpu_euclidean_norm(u)

            @test result ≈ 7.0f0
        end

        @testset "general case" begin
            u = Float32[1, 2, 2]
            result = VectorOps.gpu_euclidean_norm(u)

            @test result ≈ 3.0f0
        end

        @testset "negative values" begin
            u = Float32[-3, -4]
            result = VectorOps.gpu_euclidean_norm(u)

            @test result ≈ 5.0f0
        end
    end
end
