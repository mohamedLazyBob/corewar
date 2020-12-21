# ft_printf: recoding of the original function printf.

This Project consist of a recoding of the famous printf function in C language.
----

## Contributors :
+ Robert Bright : [@Robright20](https://github.com/Robright20)
+ Adam Khribeche : [adamkhribeche](https://github.com/adamkhribeche) 
+ Mohamed Zaboub : [@mohamedLazyBob](https://github.com/mohamedLazyBob)

## Introduction
At 42_Network schools - Including 1337-, students are not allowed to use library functions.
so we re-write our own functions, and printf is one of must have functions, so we write our own.

## Subject
+ [ft_printf_subject](/ft_printf.en.pdf)

## How To Use
1. clone this repo.
2. run the `make` command.
3. include the header files.
4. call by ft_printf, and use just as you gonna use the normal printf.
ps : this project is only tested in MAC os, I don't know it's behavios in other os.

## What ft_printf supports:
- the conversions : `c`, `s`, `p`, `d`, `i`, `o`, `u`, `x`, `X`, `f`, `e`.
- the size modifiares : l, ll, L, h, hh.
- Manages : `%%` (with the width and all the other flags.)
- the flags :  `#`, `0`, `-`, `+`, `space`, `*`, `$` and `'`.
- the minimum field-width
- the precision.
- the color and bold colors, even if this isn't suppoted by origin printf.

### Available Colores 
`red`,			`yellow`,		`green`,
`blue`,			`cyan`,			`magenta`,

`bold red`,		`bold yellow`,	`bold green`.
`bold blue`,	`bold cyan`,	`bold magenta`,

### Notes
- the float is implemented using the **``Dragon4``** algorithm, we have some prety fast results.
	- printing LDBL_MAX in 0.04s
	- printing LDBL_MIN in 0.08s

for resource of how doing it your self or how it works:
check ryanjuckett website (http://www.ryanjuckett.com/), and the docs folder i've attached.

- the $ flag is not done yet, still segfaults sometimes.
- you can use the colores this way :

	ft_printf("happy {cyan}%s{eoc} year {red}%d{eoc}", "new", 2020);

<p align="center"><b> EOC. </b></p>
