# K’th Smallest Element Selection Problem

This program is compiled by g++ on Mac_Pro. The detail information of g++ is below.
```
Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/c++/4.2.1
Apple clang version 12.0.0 (clang-1200.0.32.27)
Target: x86_64-apple-darwin19.6.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

#### Compile Command

```
g++ -std=c++11 -o selecting selecting.cpp
```



## Usage

#### Default Mode

This will output `QS.txt` and `PS.txt`.

```bash
./selecting [input.txt]
```

###### Example

```bash
./selecting input.txt
```

#### Setting Name Mode

This will output `[size]_QS.txt` and `[size]_PS.txt`.

```bash
./selecting input.txt n
```

## Generating Random Samples

The program named `random_input_generator` could generate a random sample by assigning the size.

#### Usage

```bash
./random_input_generator [size]
```

#### Example

```bash
./random_input_generator 11000
```

## Results

I used `run_batch_sample.sh` to generate and test cases in batch. The generated cases and the corresponding results are in directories - `samples`,`samples2`, and `samples3`.


