Command to run the tests:
(being in project root dir) : julia --project=. -e 'using Pkg; Pkg.test()'

Command to run the benchmarks:
(being in project root dir) : julia --project=benchmark -e 'using PkgBenchmark; results = benchmarkpkg("."); display(results)'
