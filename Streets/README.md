# Street damage evaluation test
Evaluates how damaged a street is.

### Compiling

Clone this repository and build the project using [CMake](http://www.cmake.org/download/).

```sh
$ git clone https://github.com/danielcardeenas/CVision.git
$ cd CVision/Streets/
$ cmake .
$ make
```
### Run
```sh
$ ./streets <img_to_use.jpg>
```
#####Outputs

```sh
> Size: 583x813
> Damages detected: 63
> Damage0 Dimensions: 52x17 - Non significative damage
> Damage2 Dimensions: 419x434 - Significative damage
> Damage3 Dimensions: 128x183 - Significative damage
> Damage4 Dimensions: 37x47 - Non significative damage
...
> Not good
> Evaluation: 6 (The bigger the worst)

```

If the street has no damage: 

```sh
> Size: 1460x710
> Damages detected: 3
> All good

```

### Samples

**Input**: ```Damaged/damaged1.jpg```
**Outputs**: ```Output/bad1.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Damaged/damaged1.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Output/bad1.jpg" width="320" height="240" />

**Input**: ```Damaged/damaged2.jpg```
**Outputs**: ```Output/bad2.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Damaged/damaged2.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Output/bad2.jpg" width="320" height="240" />

**Input**: ```Damaged/damaged3.jpg```
**Outputs**: ```Output/bad3.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Damaged/damaged3.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Output/bad3.jpg" width="320" height="240" />

**Input**: ```Damaged/damaged4.jpg```
**Outputs**: ```Output/bad4.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Damaged/damaged4.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Output/bad4.jpg" width="320" height="240" />

**Input**: ```Damaged/damaged5.jpg```
**Outputs**: ```Output/bad5.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Damaged/damaged5.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Output/bad5.jpg" width="320" height="240" />

**Input**: ```Clean/clean.jpg```
**Outputs**: ```Output/good1.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Clean/clean.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Output/good1.jpg" width="320" height="240" />

**Input**: ```Damaged/clean2.jpg```
**Outputs**: ```Output/good2.jpg```

<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Clean/clean2.jpg" width="320" height="240" />
<img src="https://raw.githubusercontent.com/danielcardeenas/CVision/master/Streets/Output/good2.jpg" width="320" height="240" />