using Test
using CUDA

@testset "gpu_vector_addition_to_cpu" begin
    if !CUDA.functional()
        @test_skip gpu_vector_add_to_cpu([1.0f0], [2.0f0] == [3.0f0])
    else
       @testset "basic addition" begin
            a = Float32[1, 2, 3]
            b = Float32[10, 20, 30]
            result = gpu_vector_add_to_cpu(a, b)

            @test result == Float32[11, 22, 33]
            @test result isa Vector{Float32}
        end

        @testset "zeros" begin
            a = Float32[0, 0, 0]
            b = Float32[0, 0, 0]
            result = gpu_vector_add_to_cpu(a, b)

            @test result == Float32[0, 0, 0]
        end

        @testset "negative values" begin
            a = Float32[-1, -2, -3]
            b = Float32[1, 2, 3]
            result = gpu_vector_add_to_cpu(a, b)

            @test result == Float32[0, 0, 0]
        end

        @testset "dimension mismatch" begin
            a = Float32[1, 2, 3]
            b = Float32[10, 20]

            @test_throws DimensionMismatch gpu_vector_add_to_cpu(a, b)
        end
    end  
end