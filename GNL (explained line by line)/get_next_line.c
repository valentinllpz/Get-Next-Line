/* *********************************************************************************************************************************************************************************************************************************** */
/*                                                																																			    			                           */
/*                     																																							                                   :::      ::::::::   */
/*   get_next_line.c               													COMMENTS SECTION BELOW																					                     :+:      :+:    :+:   */
/*  																																														                   +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>      									/!\ In order to display properly the comment section open this file with your favourite text editor /!\      		     +#+  +:+       +#+        */
/*                                             										Any question or suggestion? Feel free to contact me.																   +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:47:19 by vlugand-        																																					   	    #+#    #+#             */
/*   Updated: 2020/03/02 22:12:12 by vlugand-   																																							   ###   ########.fr       */
/*                                                     																																					       			               */
/* *********************************************************************************************************************************************************************************************************************************** */

#include "get_next_line.h"

int		find_index(const char *s, int c)										// Not much to explain here, a very basic function that finds the index of our '\n'.
{
	int		i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] != (char)c)
		return (-1);															// If we don't find a '\n' we will return (-1). Simply to avoid confusion if s[0] = '\n'.
	return (i);
}

int		get_line(char *str, char **line, int i)								
{
	int		len;

	*line = ft_substr(*str, 0, i);												// We assign to 'line' what is in 'str', from str[0] to str[i]. Remember, 'i' is the index where our '\n' was located.
	++i;																		// We move our index 1 position after '\n'.
	len = ft_strlen(*str + i) + 1;												// We want to know what's the lenght of the string after the first '\n'. The +1 is here to include the '\0' in 'len'.
	ft_memmove(*str, *str + i, len);											// We move what's after the first '\n' to the beginning of 'str', '\0' included to make things easy.
	return (1);																	// We ALWAYS return (1) because we call get_line only if a '\n' was found.
}

int		get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*str = NULL;
	int				ret;
	int				i;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0) 			// Here we look for basic errors our variables. We use a read 0 here to look for errors without moving our cursor.
		return (-1);
	if (str && (((i = find_index(str, '\n')) != -1))) 							// If our static string 'str' exists and we found a '\n' in it at the index 'i', let's call get_line. 
		return (get_line(&str, line, i)); 										// get_line will always return (1), since if we called this function only if a '\n' has been found, hence if a new line has been found.
	while (((ret = read(fd, buff, BUFFER_SIZE)) > 0)) 							// While we did not reach the EOF we read in buff. Also, 'ret' will get the number of bytes read, and 1 char = 1 byte.
	{
		buff[ret] = '\0';														// We finish buff[ret] with a '\0'. We use 'ret' in case 'read' does not fill all the buffer (when we reach EOF possibly).
		str = join_and_free(str, buff); 										// We join 'buff' with 'str' and we free the old 'str' to avoid memory leaks.
		if (((i = find_index(str, '\n')) != -1)) 								// Is there a '\n' in str? If yes, we will keep note of its position in 'str' in our index 'i'. If no, we'll go back to the beginning of the loop.
			return (get_line(&str, line, i)); 									// There is a '\n', so we make a line and return (1).
	}
	if (str) 																	// That's for when we already reached EOF, and there are no '\n' in our static 'str' BUT still some text.
	{
		*line = ft_strdup(str);													// We simply strdup what's left in 'str'.
		free(str);																// Now we finished our last line, so let's free 'str'.
		str = NULL;																// ALWAYS set to NULL after a malloc.
		return (ret);															// Let's return 'ret' (necessarily 0 since we got out of the 'while').
	}
	*line = ft_strdup("");														// Here we will make an empty line in case GNL is called after we finished reading the file, and line was not freed. 
	return (ret);																// Return (0).
}
																				// Enjoy! Don't copy/paste my code, you should try to understand it and make your own. Stuck? Start over, that's the best advice I was given for GNL. :)



