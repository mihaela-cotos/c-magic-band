#include "utils.h"

int main() {

    Band *band = create_band();
    Queue *operation_queue = create_queue();

    FILE *input_file, *output_file;
    input_file = fopen("data.in", "r");
    output_file = fopen("data.out", "w");

    if (input_file == NULL || output_file == NULL) {
        return 1;
    }

    char command[MAX];
    int nr_commands;
    fscanf(input_file, "%d", &nr_commands);
    fgets(command, MAX, input_file);   // skip to the next line

    for (int i = 0; i < nr_commands; ++i) {

        fgets(command, MAX, input_file);

        if (!strcmp(command, "SHOW\n")) {
            show(band, output_file);

        } else if (!strcmp(command, "SHOW_CURRENT\n")) {
            show_current(band, output_file);

        } else if (!strcmp(command, "UNDO\n")) {
            undo(band);

        } else if (!strcmp(command, "REDO\n")) {
            redo(band);

        } else  if (!strcmp(command, "EXECUTE\n")) {
            execute(band, operation_queue, output_file);

        } else {
            enqueue(operation_queue, command);
        }
    }

    free_band(band);
    free_queue(operation_queue);
    fclose(input_file);
    fclose(output_file);

    return 0;
}
