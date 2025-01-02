# bench_json4cpp
在确保 cmake/makefile/gcc or clang or msvc 都准备好的情况下，clone 项目后使用下面的命令进行一键 benchmar
```shell
cmake -DCMAKE_BUILD_TYPE=Release -B build && cmake --build build && ./build/benchmark/json_bench
```
M3Pro 的测试结果如下：

|      ns/op |           op/s | err% | total | benchmark               |
|-----------:|---------------:|-----:|------:|:------------------------|
| 540,864.85 |       1,848.89 | 1.4% |  0.65 | `Parse:nlohmann`        |
| 531,247.92 |       1,882.36 | 2.4% |  0.63 | `Parse:jsoncpp`         |
| 132,624.60 |       7,540.08 | 0.4% |  0.16 | `Parse:rapid_json`      |
| 117,324.28 |       8,523.39 | 0.9% |  0.14 | `Parse:ejson`           |
| 206,299.31 |       4,847.33 | 1.1% |  0.25 | `Stringify:nlohmann`    |
| 312,637.53 |       3,198.59 | 1.7% |  0.37 | `Stringify:jsoncpp`     |
| 126,970.87 |       7,875.82 | 0.4% |  0.15 | `Stringify:rapid_json`  |
|  74,202.38 |      13,476.66 | 0.7% |  0.09 | `Stringify:ejson`       |
|      69.67 |  14,353,255.45 | 0.2% |  0.00 | `FindMember:nlohmann`   |
|      48.09 |  20,795,755.97 | 0.4% |  0.00 | `FindMember:jsoncpp`    |
|     230.74 |   4,333,791.62 | 0.3% |  0.00 | `FindMember:rapid_json` |
|       9.55 | 104,759,643.92 | 0.1% |  0.00 | `FindMember:ejson`      |