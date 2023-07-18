#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // Lấy đường dẫn thư mục hiện tại

    char current_dir[1024];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("getcwd() error");
        return 1;
    }

    char *command = "aws cloudformation delete-stack --stack-name test";
    // Chuyển con trỏ sang thư viện hiện tại

    if (chdir(current_dir) != 0)
    {
        perror("chdir() error");
        return 1;
    }

    int result = system(command);
    if (result == -1)
    {
        perror("system() error");
        return 1;
    }

    while (1)
    {
        // Chạy lệnh xoá stack tên test
        char status[] = "aws cloudformation describe-stacks --stack-name test --query \"Stacks[].{\\\"Status\\\":StackStatus}\" --output text";
        FILE *fp = popen(status, "r");
        if (fp == NULL)
        {
            perror("popen() error");

            return 1;
        }

        char stack_status[1024] = {0};
        if (fgets(stack_status, sizeof(stack_status), fp) == NULL)

        {
            perror("fgets() error");
            return 1;
        }
        // check trạng thái của stack
        stack_status[strcspn(stack_status, "\n")] = 0;
        if (strcmp(stack_status, "DELETE_IN_PROGRESS") == 0)
        {
            printf("Delete Stack progress...\n");
        }
        else if (strcmp(stack_status, "DELETE_COMPLETE") == 0)
        {
            printf("Delete Stack compelete...\n");
        }
        pclose(fp);
        sleep(1);
    }

    return 0;
}
