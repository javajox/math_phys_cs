function R = ref(A)
  # A is a local copy; modifying it here does NOT change the original
  # variable in the script that called this function.

  # If no arguments are passed, run the benchmark and exit
  if nargin == 0
    run_benchmark();
    return;
  endif

  [rows, cols] = size(A);
  current_row = 1;
  pivot_col = 1;

  while current_row <= rows && pivot_col <= cols
    # Find pivot
    [val, row_idx] = max(abs(A(current_row:rows, pivot_col)));
    row_idx = row_idx + current_row - 1;

    if val < 1e-9
      pivot_col = pivot_col + 1;
      continue;
    endif

    # Swap rows
    A([current_row, row_idx], :) = A([row_idx, current_row], :);

    # Normalize
    A(current_row, :) = A(current_row, :) / A(current_row, pivot_col);

    # Eliminate below
    for r = current_row + 1:rows
      A(r, :) = A(r, :) - A(r, pivot_col) * A(current_row, :);
    endfor

    current_row = current_row + 1;
    pivot_col = pivot_col + 1;
  endwhile

  # Assign the final result to the output variable
  R = A;
endfunction

%!test
%! assert(ref([2]), [1], 1e-12);

%!test
%! assert(ref([0]), [0], 1e-12);

%!test
%! assert(ref([34,5]), [1, 5/34], 1e-12);

%!test
%! assert(ref([3;5]), [1;0], 1e-12);

%!test
%! assert(ref([1;0;0;0]), [1;0;0;0], 1e-12);

# --- Benchmark Helper Function ---
function run_benchmark()
  sizes = [100, 200, 400, 600, 800]; # Matrix dimensions (N x N)
  fprintf('\n%-10s | %-12s\n', 'Size (N)', 'Time (sec)');
  fprintf('---------------------------\n');

  for n = sizes
    A = rand(n, n); # Generate a random matrix

    tic;            # Start timer
    ref(A);         # Call the function
    t = toc;        # Stop timer

    fprintf('%-10d | %-12.4f\n', n, t);
  endfor
  fprintf('---------------------------\n');
  fprintf('Benchmark complete.\n');
endfunction
