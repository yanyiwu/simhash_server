# Simhash Server

[![Test](https://github.com/yanyiwu/cppjieba/actions/workflows/test.yml/badge.svg)](https://github.com/yanyiwu/cppjieba/actions/workflows/test.yml)

## Introduction

HTTP Server based on [simhash]

## Usage

Dependencies:

+ `g++ (version >= 4.1 recommended) or clang++`;

```sh
git clone --recurse-submodules https://github.com/yanyiwu/simhash_server.git
```

```sh
make
cd keyword_server
```

if you are using MacOSX, please use `make osx` .

```
./simhash.server
```

```
curl "http://127.0.0.1:11201/?s=你好世界"
```

```
curl -d "我是蓝翔 技工拖拉机学院手扶拖拉机专业的。" "http://127.0.0.1:11201"
```

[simhash]:http://github.com/yanyiwu/simhash
