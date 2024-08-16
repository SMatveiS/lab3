#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int checkdigit(char *str);  // Проверяет, является ли строка числом и преобразует её в int
char * find_and_reduce(char *str, int n, int f, int t, int c); // Преобразование строки
char * getmas(); // Получение строки
int main(int argc, char *argv[]) {
    if (argc == 1) { // Если нет опций и файлов
    	char *nstr = getmas();
    	char *fstr = find_and_reduce(nstr, 0, 1, 0, 0);
    	printf("%s", fstr);
    }
    
    else if (strcmp(argv[1], "-v") == 0) {
    	if (argc == 2) {
    	    printf("Смирнов Матвей Сергеевич, гр. N3146\nВариант: 10-2-4-3\n");
    	}
    	else
    	    fprintf(stderr, "Данная опция не поддерживает аргументы\n");
    }
    
    else {
    	FILE *f_in, *f_out; 
    	int count_files = 0;
    	int n, f, t, c; // переменные для опций
    	n = f = t = c = 0;
    	
    	int i = 1;
    	for (; i < argc; ++i) {   // перебор всех аргументов
    	    if (argv[i][0] != '-') 
    	    	break;     // если это не опция, то идём дальше и проверяем файл ли это
    	    
    	    else if (strcmp(argv[i], "-n") == 0) {
    	    	if (n) {    // Если данная опция уже была указана, то ошибка
    	    	    fprintf(stderr, "Ошибка: вы указали одинаковые опции\n");
    	    	    return EXIT_FAILURE;
    	    	}
    	    	n = 1;   
    	    }
    	    
    	    else if (strcmp(argv[i], "-c") == 0) {
    	    	if (c) {
    	    	    fprintf(stderr, "Ошибка: вы указали одинаковые опции\n");
    	    	    return EXIT_FAILURE;
    	    	}
		c = 1;
    	    }
    	    
    	    else if (argv[i][1] == 'f' && argv[i][2] == '=') {
    	    	if (f) {
    	    	    fprintf(stderr, "Ошибка: вы указали одинаковые опции\n");
    	    	    return EXIT_FAILURE;
    	    	}
    	    	if (strlen(argv[1]) == 3) {
    	    	    fprintf(stderr, "Ошибка: в опции -f не указано значение\n");
    	    	    return EXIT_FAILURE;
    	    	}
    	    	char dig[strlen(argv[i]) - 2];
    	    	strncpy(dig, &argv[i][3], strlen(argv[i]) -2);
    	    	f = checkdigit(dig);
    	    }
    	    
    	    else if (argv[i][1] == 't' && argv[i][2] == '=') {
    	    	if (t) {
    	    	    fprintf(stderr, "Ошибка: вы указали одинаковые опции\n");
    	    	    return EXIT_FAILURE;
    	    	}
    	    	if (strlen(argv[1]) == 3) {
    	    	    fprintf(stderr, "Ошибка: в опции -t не указано значение\n");
    	    	    return EXIT_FAILURE;
    	    	}
    	    	char dig[strlen(argv[i]) - 2];
    	    	strncpy(dig, &argv[i][3], strlen(argv[i]) -2);
    	    	t = checkdigit(dig);
    	    }
    	    else {
    	    	fprintf(stderr, "Ошибка: указана неподдерживаемая опция\n");
    	    	return EXIT_FAILURE;
    	    }
    	}
    	
    	for (; i < argc; ++i) { // Проход по оставшимся аргументам, если их не осталось, то в не выполнится условие i < argc
    	    if (strlen(argv[i]) > 4 && strncmp(&argv[i][strlen(argv[i]) - 4], ".txt", 4) == 0) {
    	    	if (count_files == 0) { // Первый файл - файл для чтения
    	    	    ++count_files;
    	    	    f_in = freopen(argv[i], "r", stdin);  // Теперь стандартным потоком ввода считается файл
    	            if (f_in == NULL) {
    	                fprintf(stderr, "Ошибка: не удалось открыть файл %s\n", argv[i]);
    	                return EXIT_FAILURE;
    	            }
    	    	}
    	    	
    	    	else if (count_files == 1) { // Второй файл - файл для записи
    	            ++count_files;
    	            f_out = freopen(argv[i], "a", stdout);  // Теперь стандартным потоком вывода считается файл
    	            if (f_out == NULL) {
    	                fprintf(stderr, "Ошибка: не удалось открыть файл %s\n", argv[i]);
    	                return EXIT_FAILURE;
    	            }
    	    	}
    	    	
    	    	else {
    	    	    fprintf(stderr, "Ошибка: указано слишком много файлов\n");
    	    	    return EXIT_FAILURE;
    	    	}
    	    }
    	    
    	    else {  // Если аргумент не является ни файлом, ни опцией
    	    	fprintf(stderr, "Ошибка: указан неопознанный аргумент %s\n", argv[i]);
    	    	return EXIT_FAILURE;
    	    }
    	}
    	char *nstr = getmas();
    	char *fstr = find_and_reduce(nstr, n, f, t, c);
        printf("%s", fstr);
        
        if (count_files >= 1)  // Закрываем файлы, если они были открыты
            fclose(f_in);
        if (count_files == 2)
            fclose(f_out);
    }
    
    return EXIT_SUCCESS;
} 

int checkdigit(char *str) {
    // Проверяем, что пользователь ввёл число:
    int len = strlen(str);
    for (int i = 0; i <= len-1; ++i) {  // (len-1) чтобы не учитывался последний непечатаемый символ, который учитывается операцией strlen
        if ((str[i] > 57) || (str[i] < 49)) { // Проверяем, что каждый символ натуральное число (втаблице ASCII цифры между 49 и 57 номером)
    	    printf("Ошибка: \'%s\' не является натуральным числом.\n", str);
    	    exit(EXIT_FAILURE);
    	}
    }
    return atoi(str);
}

char * getmas() {
    int i = 0;
    int count = 1;
    int ch;
    char *mas = calloc(512, sizeof(char));
    if (mas == NULL) {
        fprintf(stderr, "Не удалось выделить память. Программа завершена\n");
        exit(EXIT_FAILURE);
    }
    
    while ((ch = getchar()) != EOF) {
        mas[i] = ch;
        ++i;
        if (i == 512 * count - 1) { // Если не хватило выделенной памяти, то выделяем ещё
            ++count;
            mas = realloc(mas, 512 * count);
            if (mas == NULL) {
        	fprintf(stderr, "Не удалось выделить память. Программа завершена\n");
        	exit(EXIT_FAILURE);
            }
        }
    }
    if (mas[i-1] == '\n')
        mas[i] = '\0';
    else {
        mas[i] = '\n';
        mas [i+1] = '\0';
    }
    return mas;
}


char * find_and_reduce(char *str, int n, int f, int t, int c) {
    int count = 0;  // Счётчик символов
    int words = 0;  // Счётчик слов
    int flag = 1;   // Флаг для проверки, был ли предыдущий символ пробельным
    
    if (f == 0)
        f = 1;
    
    if (t == 0)
    	t = (int) strlen(str);
    
    if (f != 1) {  // Если предыдущий символ не пробельный
    	while (str[count + 14] != '\0' && words < f - 1) {
    	    if (isspace(str[count]) && flag == 0) {
            	++words;  // Прибавляем слово
            	++flag;   // Устанавливаем флаг
            }
            else
            	flag = 0;
            ++count;
    	}
    }
    
    if ((int) strlen(str) > 14) {
        while (str[count + 14] != '\0' && words >= f - 1 && words <= t - 1) {
            char temp_str[15]; // Массив для проверки, является ли он автомобильным номером
            int prob = 0; // Счётчик символов новой строки если нет функции -n
            if (n) {
                for (int i = 0; i < 14; ++i)
                    temp_str[i] = str[count + i];
                temp_str[15] = '\0';
            }
            
            else {
                for (int i = 0; i < 14; ++i) {
                    if (str[count + i + prob] == '\n' && i != 0) { 
                        ++prob;  // Пропускаем символ новой строки, если он не первый в строке
                        --i;
                        continue;
                    }
                    temp_str[i] = str[count + i + prob];
                }
                temp_str[15] = '\0';
            }
            
            char rus[4];
            for (int i = 0; i < 3; ++i)
                rus[i] = temp_str[11 + i];
            rus[3] = '\0';
            if (isdigit(temp_str[2]) && isdigit(temp_str[3]) && isdigit(temp_str[4]) 
            && isdigit(temp_str[9]) && isdigit(temp_str[10]) && strcmp(rus, "RUS") == 0)     { // Проверка на автомобильный номер
                if (c) { // Изменение цвета
                    char temp[strlen(str) + 8]; // Временная строка
                    strcpy(temp, str);
                    strncpy(&temp[count], "\e[33m", 6);
                    strncpy(&temp[count + 5], &str[count], 14 + prob);
                    strncpy(&temp[count + 19 + prob], "\e[m", 4);
                    strcpy(&temp[count + 22 + prob], &str[count + 14 + prob]);
                    temp[strlen(temp)] = '\0';
                    strcpy(str, temp);
                    count += 8; // Для пропуска новых символов
                }
                else {  // Кодировка markdown
                    char temp[strlen(str) + 5]; // Временная строка
                    strcpy(temp, str);
                    temp[count] = '~';
                    temp[count + 1] = '~';
                    strncpy(&temp[count + 2], &str[count], 14 + prob);
                    temp[count + 16 + prob] = '~';
                    temp[count + 17 + prob] = '~';
                    strcpy(&temp[count + 18 + prob], &str[count + 14 + prob]);
                    temp[strlen(temp)] = '\0';
                    strcpy(str, temp);
                    count += 4; // Для пропуска новых символов
                }
            }
            ++count;
            
            if (isspace(str[count]) && flag == 0) {
            	++words;
            	++flag;
            }
            else
            	flag = 0;
        }
    }
    
    return str;
}
