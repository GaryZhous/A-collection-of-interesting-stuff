#include <stdio.h>
#include <stdlib.h>

//The function isSpecial is designed to find the endpoints of the longest path in the tree, also known as the tree's diameter.

void bfs(int node, int n, int from[], int to[], int edge_count, int distance[], int* farthest_node) {
    // Initialize all distances as -1 (unvisited)
    for (int i = 0; i < n; ++i) distance[i] = -1;
    
    // Create a queue for BFS
    int queue[n];
    int start = 0; // start of the queue
    int end = 0; // end of the queue
    
    // Start from the given node
    distance[node] = 0;
    queue[end++] = node;
    
    // Standard BFS Loop
    while (start < end) {
        int current = queue[start++];
        
        // Check all adjacent nodes
        for (int i = 0; i < edge_count; ++i) {
            int next = -1;
            if (from[i] == current + 1 && distance[to[i] - 1] == -1) { // Adjusting index to be 0-based
                next = to[i] - 1;
            } else if (to[i] == current + 1 && distance[from[i] - 1] == -1) { // Adjusting index to be 0-based
                next = from[i] - 1;
            }
            
            if (next != -1) {
                distance[next] = distance[current] + 1;
                queue[end++] = next;
                
                // Keep track of the farthest node
                if (*farthest_node == -1 || distance[next] > distance[*farthest_node]) {
                    *farthest_node = next;
                }
            }
        }
    }
}

int* isSpecial(int tree_nodes, int tree_edges, int* tree_from, int* tree_to, int* result_count) {
    int* distance = malloc(tree_nodes * sizeof(int));
    int* special = calloc(tree_nodes, sizeof(int));
    *result_count = tree_nodes;
    
    // Run BFS from the first node to find one end of the diameter
    int farthest_node = 0;
    bfs(0, tree_nodes, tree_from, tree_to, tree_edges, distance, &farthest_node);
    
    // Run BFS from the farthest node found to find the actual diameter
    bfs(farthest_node, tree_nodes, tree_from, tree_to, tree_edges, distance, &farthest_node);
    
    // The two endpoints of the diameter are special
    special[farthest_node] = 1;
    
    int max_distance = distance[farthest_node];
    for (int i = 0; i < tree_nodes; ++i) {
        if (distance[i] == max_distance) {
            special[i] = 1; // Mark the node as special if it has the max distance
        }
    }
    
    // Additionally, we need to mark all nodes on the path between the two farthest nodes as special
    int current_node = farthest_node;
    while (max_distance > 0) {
        for (int i = 0; i < tree_edges; ++i) {
            if ((tree_from[i] - 1 == current_node && distance[tree_to[i] - 1] == max_distance - 1) ||
                (tree_to[i] - 1 == current_node && distance[tree_from[i] - 1] == max_distance - 1)) {
                current_node = (tree_from[i] - 1 == current_node) ? tree_to[i] - 1 : tree_from[i] - 1;
                special[current_node] = 1;
                break;
            }
        }
        max_distance--;
    }
    
    free(distance);
    return special;
}


// Remember to free the returned array after calling this function
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** tree_nodes_edges = split_string(rtrim(readline()));

    int tree_nodes = parse_int(*(tree_nodes_edges + 0));
    int tree_edges = parse_int(*(tree_nodes_edges + 1));

    int* tree_from = malloc(tree_edges * sizeof(int));
    int* tree_to = malloc(tree_edges * sizeof(int));

    for (int i = 0; i < tree_edges; i++) {
        char** tree_from_to = split_string(rtrim(readline()));

        int tree_from_temp = parse_int(*(tree_from_to + 0));
        int tree_to_temp = parse_int(*(tree_from_to + 1));

        *(tree_from + i) = tree_from_temp;
        *(tree_to + i) = tree_to_temp;
    }

    int result_count;
    int* result = isSpecial(tree_nodes, tree_edges, tree_from, tree_to, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
