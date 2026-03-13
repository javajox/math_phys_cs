using Test
using CUDA
using VectorOps

@testset "gpu_euclidean_distance" begin
    if !CUDA.functional()
        @test_skip VectorOps.gpu_euclidean_distance(Float32[1, 2], Float32[4, 6]) ≈ 5.0f0
    else
        @testset "basic case" begin
            u = Float32[1, 2]
            v = Float32[4, 6]

            result = VectorOps.gpu_euclidean_distance(u, v)

            @test result ≈ 5.0f0
            @test result isa Float32
        end

        @testset "identical vectors" begin
            u = Float32[1, 2, 3]
            v = Float32[1, 2, 3]

            result = VectorOps.gpu_euclidean_distance(u, v)

            @test result ≈ 0.0f0
        end

        @testset "negative values" begin
            u = Float32[-1, -2]
            v = Float32[2, 2]

            result = VectorOps.gpu_euclidean_distance(u, v)

            @test result ≈ 5.0f0
        end

        @testset "single element" begin
            u = Float32[3]
            v = Float32[10]

            result = VectorOps.gpu_euclidean_distance(u, v)

            @test result ≈ 7.0f0
        end

        @testset "dimension mismatch" begin
            u = Float32[1, 2, 3]
            v = Float32[1, 2]

            @test_throws DimensionMismatch VectorOps.gpu_euclidean_distance(u, v)
        end
    end
end
