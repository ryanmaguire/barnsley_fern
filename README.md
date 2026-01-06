# Table of Contents
1. [Barnsley Fern](#bf)
2. [Benchmarks](#benchmarks)
3. [License](#license)

# Barnsley Fern <a name="bf"></a>
Code for rendering the Barnsley fern in different languages.

![Barnsley Fern](https://github.com/ryanmaguire/barnsley_fern/blob/main/assets/barnsley_fern.png "Barnsley Fern")

# Benchmarks
These benchmarks used a Ryzen 9 7950x on Debian 12.

| Language | Implementation | Time (s) | Version                                  |
| -------- | -------------- | -------- | ---------------------------------------- |
| C        | gcc            |    0.478 | gcc (Debian 12.2.0-14) 12.2.0            |
| C        | clang          |    0.480 | Debian clang version 14.0.6              |
| C++      | g++            |    0.485 | g++ (Debian 12.2.0-14) 12.2.0            |
| C++      | clang++        |    0.488 | Debian clang version 14.0.6              |
| C        | pcc            |    0.523 | Portable C Compiler 1.2.0.DEVEL 20220331 |
| C        | tcc            |    0.799 | tcc version 0.9.27                       |
| Python   | Pypy           |    1.165 | PyPy 7.3.11 with GCC 12.2.0              |
| Go       | golang         |    1.220 | go 1.19.8                                |
| Go       | gccgo          |    1.895 | gccgo (Debian 12.2.0-14) 12.2.0          |
| Python   | CPython        |   14.825 | Python 3.11.2                            |

# License
    barnsley_fern is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    barnsley_fern is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with barnsley_fern.  If not, see <https://www.gnu.org/licenses/>.
