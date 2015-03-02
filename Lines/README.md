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
### Explanation

### Samples
**Input**: ```img/chessboard1.png```
**Outputs**: ```chess_100.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/img/chessboard1.png" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/chess_100.jpg" width="320" height="240" />

**Input**: ```img/chessboard1.png```
**Outputs**: ```chess_200.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/img/chessboard1.png" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Lines/chess_200.jpg" width="320" height="240" />
