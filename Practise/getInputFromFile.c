                        iterator++;
                        stringIndex = 0;
                        while(ch1 != '<')
                        {
                                *(str+stringIndex) = ch1;
                                stringIndex++;
                                fileMarker += (char)fread(&ch1,1,1,f);
                        }
                        *(str+stringIndex) = '\0';
                //      printf("\nSTR:%s\n",str);
                choice = ((iterator%3)+1) + 48;
                switch(choice)
                {
                        case NAME:
                                name = (char*)malloc(string_length(str));
                                stringCopy(str,name);
                                break;
                        case ROLL:
                                roll = string_to_number(str);
                //              printf("\nRoll:%d\n",roll);
                                break;
                        case MARK:
                                mark = string_to_number(str);
                //              printf("\nMark:%d\n",mark);
                                append(head,tail,name,roll,mark);
                                free(name);
                                name = NULL;
                                break;
                }
