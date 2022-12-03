#include <unistd.h>
#include <stdarg.h>

int g_var = 0;

void put_number(int n, char *base, int len){
	if (n >= len)
		put_number(n / len, base, len);
	g_var += write(1, &base[n % len], 1);
}

int ft_printf(const char *format, ...){
	int i = 0;
	va_list list;
	int j = 0;
	va_start(list, format);
	while (format[i]){
		if (format[i] == '%'){
			i++;
			if(format[i] == 's'){
				j = 0;
				char *str = va_arg(list, char *);
				if(!str)
					str = "NULL";
				while(str[j]){
					g_var += write(1, &str[j], 1);
					j++;
				}
			}
			else if(format[i] == 'd'){
				long numb = va_arg(list, int);
				if(numb < 0){
					g_var += write(1, "-", 1);
					numb = -numb;
				}
				put_number(numb, "0123456789", 10);
			}
			else if(format[i] == 'x'){
				int hex = va_arg(list, int);
				put_number(hex, "0123456789abcdef", 16);
			}
			i++;
		}
		else{
			g_var += write(1, &format[i], 1);
			i++;
		}
	}
	va_end(list);
	return (g_var);
}

int main(){
	char name[] = "Henrique";
	int age = 25;
	int res = ft_printf("sou o %s tenho %d anos", name, age);
	ft_printf("\nNumber of characters writen: %d", res);
}