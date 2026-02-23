module MyMatrixProject

export sum_matrices

function sum_matrices(A::AbstractArray, B::AbstractArray)
    size(A) == size(B) || throw(DimensionMismatch("Dimension mismatch!"))
    return A + B
end

end
