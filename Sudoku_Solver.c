#include<stdio.h>
int grid[9][9]={0};
int filled[9][9]={0};
int possibility[9][9][10]={0};

void setPossiblity()
{//Setting possibility of all data(except zero) at all positions equal to one
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            for(int k=1;k<10;k++)
                possibility[i][j][k]=1;
}

void showGrid()
{//function to print the grid
    printf("\n");
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            printf("%d ",grid[i][j]);
            if(j%3==2)
                printf(" ");
        }
        printf("\n");
        if(i%3==2)
            printf("\n");
    }
    findVacantPositions();
}

void placeNumber(int data,int row,int column)
{//places the data at requires position
    for(int i=0;i<9;i++)
    {//to rule out possibility of that data in that row
        possibility[row][i][data]=0;
    }
    for(int i=0;i<9;i++)
    {//to rule out possibility of that data in that column
        possibility[i][column][data]=0;
    }
    int p=row%3;
    int q=column%3;
    for(int i=row-p;i<=row+(2-p);i++)
    {//to rule out possibility of that data in entire 3 X 3 block
        for(int j=column-q;j<=column+(2-q);j++)
        {
            possibility[i][j][data]=0;
        }
    }
    grid[row][column]=data;//place the data
    filled[row][column]=1;//mark that position as filled
}

void fillInSomeNumbers()
{//to initialize the data of Pre-Given Grid
    int data,row,column,k;
    printf("Enter Number of Pre-Given Data\n");
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
        scanf("%d %d %d",&data,&row,&column);
        placeNumber(data,row,column);
    }
}

int findVacantPositions()
{//to find Vacancy in Grid
    int counter=0;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(filled[i][j]==0)
            {
                counter++;
            }
        }
    }
    printf("Vacant Positions are %d\n",counter);
    return counter;
}

void solveSudoku()
{//the function responsible for solving the sudoku
    int b[10]={0};
    if(findVacantPositions()==0)
    {
        printf("Solved Sudoku\n");
        return;
    }
    else
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                if(filled[i][j]==1)
                    continue;

                int counter=0;int data=0;
                for(int k=0;k<10;k++)
                {
                    if(possibility[i][j][k])
                    {
                        counter++;
                        data=k;
                    }
                }
                //If there no possibility to place any data on a position then it's impossible to solve sudoku
                if(counter==0)
                    printf("Impossible\n");

                //Place the number if there's certainty of a data at that position
                if(counter==1)
                    placeNumber(data,i,j);

                b[counter]++;
            }
        }
    }
    for(int i=0;i<10;i++)
    {
        printf("Positions having %d possibility=%d\n",i,b[i]);
    }
    //solve recursively till all the positions having single possibility aren't filled
    if(b[1]!=0)
            solveSudoku();
}

void showPossibility()
{//function to just check possibility of all positions if needed(for debugging)
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            for(int k=0;k<10;k++)
                printf("%d",possibility[i][j][k]);
        }
    }
}

int main()
{
    findVacantPositions();
    setPossiblity();
    fillInSomeNumbers();
    showGrid();
    solveSudoku();
    showGrid();
}
