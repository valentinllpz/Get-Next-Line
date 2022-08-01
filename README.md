# Get Next Line (2019)

This [42](https://42.fr/en/homepage/) project aims to make us write a function that allows us to open and read a file line by line using file descriptors and store its content in a `char **` (string array).

## 🧭 Usage

Clone the repository and access it with `cd`. From there, use the following command :
```
make bonus
```

## 📚 Functions explained in details

`int		find_index(const char *s, int c)`

Not much to explain here, a very basic function that finds the index of our '\n'.
If we don't find a '\n' we will return (-1). Simply to avoid confusion if s[0] = '\n'.

`int		get_line(char *str, char **line, int i)`

1. We assign to 'line' what is in 'str', from str[0] to str[i]. Remember, 'i' is the index where our '\n' was located.
2. We move our index 1 position after '\n'.
3. We want to know what's the lenght of the string after the first '\n'. The +1 is here to include the '\0' in 'len'.
4. We move what's after the first '\n' to the beginning of 'str', '\0' included to make things easy.
5. We ALWAYS return (1) because we call get_line only if a '\n' was found.

`int		get_next_line(int fd, char **line)`

1. First, we look for basic errors our variables. We use a read 0 here to look for errors without moving our cursor.
2. If our static string 'str' exists and we found a '\n' in it at the index 'i', let's call get_line. 
3. get_line will always return (1), since if we called this function only if a '\n' has been found, hence if a new line has been found.
4. While we did not reach the EOF we read in buff. Also, 'ret' will get the number of bytes read, and 1 char = 1 byte.
5. We finish buff[ret] with a '\0'. We use 'ret' in case 'read' does not fill all the buffer (when we reach EOF possibly).
6. We join 'buff' with 'str' and we free the old 'str' to avoid memory leaks.
7. Is there a '\n' in str? If yes, we will keep note of its position in 'str' in our index 'i'. If no, we'll go back to the beginning of the loop.
8. There is a '\n', so we make a line and return (1).
9. That's for when we already reached EOF, and there are no '\n' in our static 'str' BUT still some text.
10. We simply strdup what's left in 'str'.
11. Now we finished our last line, so let's free 'str'.
12. ALWAYS set to NULL after a malloc.
13. Let's return 'ret' (necessarily 0 since we got out of the 'while').
14. Here we will make an empty line in case GNL is called after we finished reading the file, and line was not freed. 
15. Return (0).

--------------------------------------------------------------------------------

Please don't copy/paste my code, you should try to understand it and make your own.

Stuck? Start over, that's the best advice I was given for GNL. :)

Good luck!

