
void get_coefficients()
{
	int index1 = 1,index2 = 0;
        char str1[9];
	while(equation[index1] != '=')
        {
                index++;
        }
        equation[index1] = '\0';
        index1++;
        while(equation[index1] != '\0')
        {
                str1[index2++] = equation[index1++]; 
        }
        str1[index2] = '\0';
        printf("constant:%s\n",str1);
	index1 = 1;
        while(equation[index1] != '+' && equation[index1] != '-')
        {
                if(equation[index1] == '\0')
                {
                        *no_of_var = 1;
                        var_name = equation[index1-1];
                        str1[index2] = '\0';
                        coefficient1[0] = string_to_number(str1);
                        coefficient1[1] = 0;
                        printf("Single coefficient\n");
                        return 0;
                }
	str1[index2++] = equation[index1-1];
                index1++;
        }
        printf("%s\n",str1);
	*var_x = equation[index1-1];
        str1[index2] = '\0';
        printf("x:%s\n",str1);
        coefficient[0] = string_to_number(str1);
        printf("a:%d\n",coefficient[0]);
        index1++;
        index2 = 0;
        while(equation[index1] != '=')
        {
                str1[index2++] = equation[index1-1];
                index1++;
        }
        label: *var_y = equation[index1-1];
	str1[index2] = '\0';
        printf("y:%s\n",str1);
        coefficient[1] = string_to_number(str1);
        printf("b:%d\n",coefficient[1]);



}

