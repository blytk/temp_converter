#include <stdio.h>
#include <stdlib.h>

// Set number of options (Celsius, Fahrenheit, Kelvin)
const unsigned int N = 3;

int convert(float unit_amount, unsigned int option_input, unsigned int option_output);

int main(int argc, char *argv[])
{
    // Input type (celsius, fahrenheit, kelvin)
    printf("Select input temperature units:\n");
    printf("1 -> Celsius\n");
    printf("2 -> Fahrenheit\n");
    printf("3 -> Kelvin\n");
    unsigned int option_input;
    scanf("%u", &option_input);
    float unit_amount;
    printf("Enter unit amount: ");
    scanf("%f", &unit_amount);
    // Output Type (celsius, fahrenheit, kelvin)
    printf("Select output temperature units for conversion:\n");

    unsigned int option_output;
    char *options[N];
    options[1] = "Celsius";
    options[2] = "Fahrenheit";
    options[3] = "Kelvin";
    do
    {
        if (option_input != 1)
        {
            printf("1 -> %s\n", options[1]);
        }
        if (option_input != 2)
        {
            printf("2 -> %s\n", options[2]);
        }
        if (option_input != 3)
        {
            printf("3 -> %s\n", options[3]);
        }
        scanf("%u", &option_output);
    }
    while (option_output == option_input || option_output > N || option_output < 0);
    
    // convert will receive the amount of units, the option input, and the option_output
    int converted_units = convert(unit_amount, option_input, option_output);
    if (option_output == 3 && converted_units < 0)
    {
        converted_units = 0;
    }
    printf("%.0fº %s is similar to %iº %s\n", unit_amount, options[option_input], converted_units, options[option_output]);
}

int convert(float unit_amount, unsigned int option_input, unsigned int option_output)
{
    // option 1 = Celsius
    // option 2 = Fahrenheit
    // option 3 = Kelvin
    float output_int;
    if (option_input == 1) // celsius input
    {
        if (option_output == 2) // convert to fahrenheit F = C x 9/5 + 32
        {
            output_int = unit_amount * 1.8 + 32;
        }
        else if (option_output == 3) // convert to kelvin K=C+273.15
        {
            output_int = unit_amount + 273;
        }
    }
    else if (option_input == 2) // fahrenheit input
    {
        if (option_output == 1) // convert to celsius C= 5/9 ​×(F−32)
        {
            output_int = 0.55 * (unit_amount - 32);
        }
        else if (option_output == 3) // convert to kelvin (need to convert to celsius first apparently) // can I call the function from within the function?
        {
            output_int = convert(unit_amount, 2, 1);
            output_int = convert(unit_amount, 1, 3);
        }
    }
    else if (option_input == 3) // kelvin input
    {
        // 0 is minimum temp (absolute zero) in kelvin scale
        if (unit_amount < 0)
        {
            unit_amount = 0;
        }
        if (option_output == 1) // convert to celsius C=K−273.15
        {
            output_int = unit_amount - 273;
        }
        else if (option_output == 2) // convert to fahrenheit (kelvin to celsius > celsius to fahrenheit)
        {  
            output_int = convert(unit_amount, 3, 1);
            output_int = convert(output_int, 1, 2);
        }
    }
    return (int)output_int;
}