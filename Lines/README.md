# Lines detection
Detects the lines of a given image using [Hough transform](http://en.wikipedia.org/wiki/Hough_transform).

### Compiling

Clone this repository and build the project using [CMake](http://www.cmake.org/download/).

```sh
$ git clone https://github.com/danielcardeenas/CVision.git
$ cd CVision/Lines/
$ cmake .
$ make
```
### Run
```sh
$ ./lines <img_to_use.jpg>
```
#####Outputs

```sh
> lines: 25 100
> Line 0:
> y = mx + -167
> Line 1:
> y = mx + 374
...
> Time elapsed: 300 Miliseconds

```


**lines:** [number of lines detected] [threshold used]

**Line** [line id]: <line equiation>

**Time elapsed:** [Miliseconds]

### Explanation

### Samples
#####Threshold: 100 votes

**Input**: ```img/chessboard1.png```
**Outputs**: ```chess_100.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/img/chessboard1.png" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/chess_100.jpg" width="320" height="240" />

#####Threshold: 200 votes

**Input**: ```img/chessboard1.png```
**Outputs**: ```chess_200.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/img/chessboard1.png" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/chess_200.jpg" width="320" height="240" />
