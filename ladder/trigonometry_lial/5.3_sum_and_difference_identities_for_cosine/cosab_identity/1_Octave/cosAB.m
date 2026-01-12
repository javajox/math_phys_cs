function result = cosAB(a, b)
  % --- THE MISSING TRIGGER ---
  if (nargin == 0)
    run_cosAB_benchmark(); % Call the function at the bottom
    return;
  endif
  % ---------------------------

  result = cos(a) * cos(b) - sin(a) * sin(b);
endfunction

%!test
%! assert(cosAB(0, 0), 1);

%!test
%! assert(cosAB(pi/2, pi/2), -1);

%!test
%! assert(cosAB(pi, pi), 1);

%!test
%! assert(cosAB((3*pi)/2, (3*pi)/2), -1)

% BENCHMARK SECTION (Now this gets called by the trigger above)
function run_cosAB_benchmark()
  printf("\n--- Starting Benchmark ---\n");

  N = 1000000;
  a = 1.0;
  b = 2.0;

  tic();
  for i = 1:N
    val = cosAB(a, b);
  endfor
  elapsed = toc();
  
  printf("Result: %d iterations took %.4f seconds\n", N, elapsed);
  printf("--- Benchmark Complete ---\n");
endfunction