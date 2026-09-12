To change vector dimensions modify N inside

```c

int main() {

&#x20;   int N = 100;

&#x20;   create\_file(N)

}

```

in the create\_x\_y\_\*.c files and adjust the file\_\*\_vector names in the .conf files

```

file\_x\_vector = ./outputdir/vector\_N\_<insert\_new\_N\_here>\_x.dat

file\_y\_vector = ./outputdir/vector\_N\_<insert\_new\_N\_here>\_y.dat

```

Then compile and run the Makefiles with

```

make run

```



