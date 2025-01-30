int main()
{
    int arr<:5:> = <% 5, 4, 3, 2, 1 %>;
    if (1<:arr:> == 5 && ((printf("true-case\n"), 1)))
    <% 
        goto end;
    %>
    printf("false-case\n");
    end:
    int i = 5;
    printf("%d\n", -~i);


    (2<:arr:> == 5 && ((printf("true-case\n"), 1))) || ((printf("false-case\n"), 1));
}
