# todo
Simple CLI app build using C++26. It was built to efficiently store todo lists in project similar to git.

## Features
- Create tasks and assign description to them
- Remove tasks
- Change task state (todo, doing, done)
- List all tasks in project

## Installation
```bash
git clone https://github.com/edving2009/todo.git
cd todo
```

***I recommend putting todo executable in your PATH so you can run it from anywhere***

## Building
```bash
cmake -S . -B build
cmake --build build
```

## Usage
```bash
todo help
```
```bash
todo add task-name description
```

```bash
todo remove task-name
```

```bash
todo list
```

```bash
todo change task-name state
```

### There is also shortcuts
```bash
todo a task-name description
```

```bash
todo r task-name
```

```bash
todo l
```

```bash
todo c tash-name state
```
