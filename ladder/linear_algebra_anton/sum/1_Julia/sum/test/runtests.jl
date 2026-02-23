using Test
using MyMatrixProject

@testset "MyMatrixProject.jl" begin

    @testset "Basic Addition" begin
        # Test with integers
        A = [1 2; 3 4]
        B = [5 6; 7 8]
        @test sum_matrices(A, B) == [6 8; 10 12]

        # Test with floating point numbers
        C = [1.5 2.5]
        D = [0.5 0.5]
        @test sum_matrices(C, D) == [2.0 3.0]
    end

    @testset "Mathematical Identities" begin
        A = rand(3, 3)
        Z = zeros(3, 3)
        
        # A + 0 = A
        @test sum_matrices(A, Z) ≈ A
        
        # A + (-A) = 0
        @test sum_matrices(A, -A) ≈ Z
    end

    @testset "Edge Cases" begin
        # Test with 1x1 matrix
        @test sum_matrices([5], [10]) == [15]
        
        # Test with empty matrices
        @test sum_matrices(Float64[;;], Float64[;;]) == Float64[;;]
    end

    @testset "Error Handling" begin
        # Test that dimension mismatch throws the correct error
        A = [1 2; 3 4]      # 2x2
        B = [1 2 3; 4 5 6]  # 2x3
        
        @test_throws DimensionMismatch sum_matrices(A, B)
    end

end
