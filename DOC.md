# Log while doing

## Questions

- [x] Boundary
- [x] Initialization of f and u

## TODO

- [ ] Copy the entire array at the last step, instead of a pointer swap
- [ ] Use "first touch" technique to initialize the data, modified on.
  - Starts from the naîve version 
- [ ] Write the all compiler options in one `-O3 -ffast-math -unroll`
  - Record the data and Compare the results
  - Starts from the naîve version

## Attention

- do not do the serialized parallelization
- use `export OMP_NUM_THREADS=4` to set the number of threads, as the default is 1
- OPT	= -g -fopenmp -O3 -ffast-math 
- Note: Setting OMP_DISPLAY_ENV=verbose is your friend here!

## Potential Improvements

- [ ] Cache-friendly loop for serial version

## Log

- [x] Serial
  - [x] Jacobian
    - [ ] Test
      - Different N
      - Covergence of the iterations/stop criterion
  - [o] Gaussian
    - [ ] Test
      - Compare with the Jacobian
        - convergence behaviour between the two methods
        - the number of iterations per second,
                either based on the whole grid or on a per grid point basis
- [ ] Parallell
  - [ ] Jacobian
    - [x] Simple Version
    - [x] Optimized Version
      - [x] Expanded Parallel regions
        - Parallell region outside the `do-while` loop
            - will only work for small system: 100 - 200
      - [x] data initialization
        - In the Rud
            - will only work for large matrix: 1000 - 2000
    - [ ] Scale // only on the naive one
      - [ ] How different version scales
        - measure the speed-up (Amdahl’s law).
            - Just need to plot the speed-up
        - Do this for different numbers of grid points (memory footprint)
        - [ ] Think about ways to optimize the runtime behavior (thread placement, etc.).
          - What does this mean?
      - [?] "Does the code scale as expected (discuss)?"  
        - what does this mean? the scale meaning the above Optimized Version?
      - [ ] Compiler option
      - [ ] Record the total execution time (wall-clock time)
    - [ ] Total performance in FLOPS
      - [ ] For large memory  
        - [?] how large is considered large enough? // as long as it is greater than L3 Chache, compute by hand 
      - [ ] for different number of threads
      - [ ] Explain the limiting factor
      - [ ] How does the measured performance correspond to the max
        - [?] what does this mean? what max?
      - [ ] performance of the hardware used
        - [?] what hardware? Memory? CPU ? how to metric?
