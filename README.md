# shiny-octo-palm-tree

[![Build Status](https://travis-ci.org/jbreitbart/shiny-octo-palm-tree.svg?branch=master)](https://travis-ci.org/jbreitbart/shiny-octo-palm-tree)
[![Coverage Status](https://coveralls.io/repos/github/jbreitbart/shiny-octo-palm-tree/badge.svg?branch=master)](https://coveralls.io/github/jbreitbart/shiny-octo-palm-tree?branch=master)
[![CodeFactor](https://www.codefactor.io/repository/github/jbreitbart/shiny-octo-palm-tree/badge)](https://www.codefactor.io/repository/github/jbreitbart/shiny-octo-palm-tree)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/45fe67e167934068b22d6b4cdfbb19ab)](https://app.codacy.com/app/jbreitbart/shiny-octo-palm-tree?utm_source=github.com&utm_medium=referral&utm_content=jbreitbart/shiny-octo-palm-tree&utm_campaign=Badge_Grade_Dashboard)

This repository is designed to allow you to easily learn to write better `C++` code. In the `task` directory are various programming tasks that you may choose to solve. If you are interested in solving one of them please proceed as follows:

1. Fork this repository
2. Clone your fork and edit the task you want to solve. Feel free to directly edit the existing folder or create a copy and edit the CMake files to avoid name conflicts.
3. Create a pull request for this repository

For every pull request you will get:
* They are compiled with various compilers (currently `gcc` and `clang`).
* One of the compiler runs also includes output of `clang-tidy`.
* We run your unit tests and provide the code coverage.
* There are also two code quality linters enabled that may provide useful information.
In general, you may to choose not to fix every compiler or linter warning, but you should try to understand the origin of these warnings.

**Note**: We will not merge every pull request that is sent to this repo. Please close them, once you have finished a task.

## Howto build the repository

In general it can be build like any other CMake project. A simple approach would be to run:

```bash
mkdir build
cd build
cmake ..
make
make test
```

This should build the software and run the test cases.

## FAQ

### Why is there not code coverage reported for my pull request?
Code coverage reports are only generated if every other test is passed successfully.
