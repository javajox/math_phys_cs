function result = cosAB(a, b)
  result = cos(a) * cos(b) - sin(a) * sin(b)
endfunction 

%!test
%! assert(cosAB(0, 0), 1);

%!test
%! assert(cosAB(pi/2, pi/2), -1);

%!test
%! assert(cosAB(pi, pi), 1);

%!test
%! assert(cosAB((3*pi)/2, (3*pi)/2), -1)