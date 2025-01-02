# bench_json4cpp
在确保 cmake/makefile/gcc or clang or msvc 都准备好的情况下，clone 项目后使用下面的命令进行一键 benchmar
```shell
cmake -DCMAKE_BUILD_TYPE=Release -B build && cmake --build build && ./build/benchmark/json_bench
```
M3Pro 的测试结果如下：

|      ns/op |          op/s | err% | total | benchmark               |
|-----------:|--------------:|-----:|------:|:------------------------|
| 547,240.60 |      1,827.35 | 3.3% |  0.65 | `Parse:nlohmann`        |
| 537,145.30 |      1,861.69 | 0.8% |  0.64 | `Parse:jsoncpp`         |
| 134,859.05 |      7,415.15 | 0.9% |  0.16 | `Parse:rapid_json`      |
|  49,526.39 |     20,191.25 | 2.6% |  0.06 | `Parse:sonic_json`      |
| 116,495.41 |      8,584.03 | 0.3% |  0.14 | `Parse:ejson`           |
| 206,079.69 |      4,852.49 | 0.6% |  0.25 | `Stringify:nlohmann`    |
| 320,726.38 |      3,117.92 | 0.2% |  0.38 | `Stringify:jsoncpp`     |
| 131,007.98 |      7,633.12 | 0.5% |  0.15 | `Stringify:rapid_json`  |
|  11,907.37 |     83,981.61 | 0.3% |  0.01 | `Stringify:sonic_json`  |
|  76,992.07 |     12,988.35 | 0.9% |  0.09 | `Stringify:ejson`       |
|      67.95 | 14,715,735.07 | 0.5% |  0.00 | `FindMember:nlohmann`   |
|      57.35 | 17,436,791.63 | 1.2% |  0.00 | `FindMember:jsoncpp`    |
|     254.65 |  3,926,892.95 | 1.8% |  0.00 | `FindMember:rapid_json` |
|     242.82 |  4,118,239.22 | 2.0% |  0.00 | `FindMember:sonic_json` |
|      10.74 | 93,138,367.92 | 0.1% |  0.00 | `FindMember:ejson`      |

自 2025-01-02 加入了字节开源的 Sonic-Cpp 作为对比，发现其性能形成了成倍碾压。。。
但 ejson4cpp 在简洁好用的同时确实达到了和 rapid-json 在同一个性能水平