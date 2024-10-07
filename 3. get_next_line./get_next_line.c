#include "get_next_line.h"
#include <unistd.h>

// 1. read and append to remaining
// 2. extract line from remaining
// 3. remove line from remaining

// Function to read data and append to remaining buffer
char	*ft_read_to_remaining(int fd, char *remaining)
{
	char	*buffer;
	int		bytes_read;

	// Allocate buffer for reading
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);

	bytes_read = 1; // Start reading
	while (!ft_strchr(remaining, '\n') && bytes_read != 0)
	{
		// Read data into buffer
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1) // Handle read error
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0'; // Null-terminate the buffer

		// Append buffer content to remaining
		remaining = ft_strjoin(remaining, buffer);
	}

	free(buffer); // Free the temporary buffer
	return (remaining);
}

// MAIN FUNCTION
char	*get_next_line(int fd)
{
	char		*line;
	static char	*remaining; // Static buffer to store leftover data

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);

	// Read data and update remaining buffer
	remaining = ft_read_to_remaining(fd, remaining);
	if (!remaining)
		return (NULL);

	// Extract the line from remaining buffer
	line = ft_get_line(remaining);

	// Update remaining buffer to remove the returned line
	remaining = ft_new_remaining(remaining);

	return (line);
}

// Function to extract a line from remaining buffer
char	*ft_get_line(char *remaining)
{
	int		i;
	char	*line;

	i = 0;
	if (!remaining[i])
		return (NULL);

	// Find newline or end of string
	while (remaining[i] && remaining[i] != '\n')
		i++;

	// Allocate memory for the line (including '\n' and null terminator)
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);

	// Copy the characters of the line
	i = 0;
	while (remaining[i] && remaining[i] != '\n')
	{
		line[i] = remaining[i];
		i++;
	}

	// Add the newline character if present
	if (remaining[i] == '\n')
	{
		line[i] = remaining[i];
		i++;
	}

	line[i] = '\0'; // Null-terminate the line
	return (line);
}

// Function to update remaining buffer after returning a line
char	*ft_new_remaining(char *remaining)
{
	int		i;
	int		j;
	char	*new_remaining;

	i = 0;

	// Find the newline in the remaining buffer
	while (remaining[i] && remaining[i] != '\n')
		i++;

	// If no newline is found, free remaining and return NULL
	if (!remaining[i])
	{
		free(remaining);
		return (NULL);
	}

	// Allocate memory for the new remaining buffer
	new_remaining = (char *)malloc(sizeof(char) * (ft_strlen(remaining) - i + 1));
	if (!new_remaining)
		return (NULL);

	// Skip past the newline character
	i++;
	j = 0;

	// Copy the rest of the string after the newline
	while (remaining[i])
		new_remaining[j++] = remaining[i++];

	new_remaining[j] = '\0'; // Null-terminate the new remaining buffer

	free(remaining); // Free the old remaining buffer
	return (new_remaining);
}
