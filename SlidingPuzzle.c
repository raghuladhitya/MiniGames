#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

int **play(int **box, int size);
int **shuffle(int **box,int size);
void display(int **box, int size);

int *IndexFinder(int **box,int size);
int check(int **box,int size);
int **swap(int **box,int row1,int col1,int row2,int col2,int size);

int arr[2];
int main(){
  
	int size,i,j,value;
	printf("\nEnter the box size of the box: ");
	scanf("%d",&size);
    value = size;
	int **box,count=1;

    box = (int **)malloc(size * sizeof(int *));                         //Constrction of the board with numerical values
    for(i=0;i<size;i++){
        box[i] = (int *)malloc(size * sizeof(int));
        for(j=0;j<size;j++){
            box[i][j] = count;
            count++;
        }
    } 
    
    display(box,value);                                                  
	box = shuffle(box,value);                                            //shuffling the board randomly for 100 times 
    display(box,value);
    box = play(box,value);                                               //User to use the arrow keys to play the game
    check(box,value);                                                    //checking whether the sliding puzzle is solved or not
    
	return 0;

}
int **play(int **box,int size){                                           // Method to perform the sliding operation
  
  int row,column;
  int flag=0,count=0;
  char direction;
  int *arr;

  arr = IndexFinder(box,size);                                            //To find the position of the empty space or the largest number 

  row = arr[0];
  column = arr[1];
  
  
  while(flag == 0){
    getch();                                                               //Getting ascii value of arrows in the keyboard
    direction = getch();
    switch(direction){                                                     //Sliding operation using while and switch cases
      case 72:
        if(row + 1 < size){
            system("cls");
            box = swap(box,row,column,row+1,column,size);
            row = row + 1;
            display(box,size);
            count++;
            if(check(box,size)){
                printf("The puzzle is solved by %d moves",count);
                return box;
            }
        }else{
            printf("Out of Bounds");
        }
        break;

      case 80:
        if(row - 1 >= 0){
            system("cls");
            box = swap(box,row,column,row-1,column,size);
            row = row - 1;
            display(box,size);
            count++;
            if(check(box,size)){
                printf("The puzzle is solved by %d moves",count);
                return box;
            }
        }else{
            printf("Out of Bounds");
        }
        break;

      case 75:
        if(column + 1 < size){
            system("cls");	
            box = swap(box,row,column,row,column+1,size);
            column = column + 1;
            display(box,size);
            count++;
            if(check(box,size)){
                printf("The puzzle is solved by %d moves",count);
                return box;
            }
        }else{
            printf("Out of Bounds");
        }
        break;

      case 77:
        if(column - 1 >= 0){
            system("cls");	
            box = swap(box,row,column,row,column-1,size);
            column = column - 1;
            display(box,size);
            count++;
            if(check(box,size)){
                printf("The puzzle is solved by %d moves",count);
                return box;
            }
        }else{
            printf("\nOut of Bounds");
        }
        break;
      case 88:
        
        flag = 1;
        return box;
        break;
    }
  }
  return box;
}


int **shuffle(int **box,int size){                                                    //Using rand() method and generating possible random 
    int row,column,i,j;                                                               //puzzle to which it can be solvable
    int start=0,stop=3;
    int number;

    row = size - 1;
    column = size - 1;

    srand(time(0));

    for(i=0;i<100;i++){                                                               //shuffling 100 times and each time program runs, different 
        int number = (rand() % (stop - start + 1)) + 1;                               //puzzle is generated
        switch(number){                                                               //sliding operation for all cases is done
            case 0:
                if(row + 1 < size){
                    box = swap(box,row,column,row+1,column,size);
                    row = row + 1;
                }
                break;
            case 1:
                if(row - 1 >= 0){
                    box = swap(box,row,column,row-1,column,size);
                    row = row - 1;
               }
                break;
            case 2:
                if(column + 1 < size){
                    box = swap(box,row,column,row,column+1,size);
                    column = column + 1;
                }
                break;
			case 3:
                if(column - 1 >= 0){
                    box = swap(box,row,column,row,column-1,size);
                    column = column - 1;
                }
                break;
        }
    } 
    return box;
}

int check(int **box,int size){                                                        //Check Function to tell whether the 
    int i,j,value = 1;                                                                //user solved the puzzle or not        
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(box[i][j] == value){
                value++;
            }
        }
    }
    if(value - 1 == size*size){
        return 1;
    }else{
        return 0;
    }

}
int **swap(int **box,int row1,int col1,int row2,int col2,int size){                    //Swap function
    box[row2][col2] = box[row2][col2] + box[row1][col1];
	box[row1][col1] = box[row2][col2] - box[row1][col1];
	box[row2][col2] = box[row2][col2] - box[row1][col1];
	
    if(box[row1][col1] == 0){
	    box[row1][col1] = size*size;
    }else if(box[row2][col2] == 0){
        box[row1][col1] = size*size;
    }
    return box;

}

void display(int **box,int size){                                                               //Display function 
    int i,j;
  
  
    for(i=0;i<size;i++){
        printf("\n");
        printf("|\t");
        for(j=0;j<size;j++){
            if(box[i][j]!=size*size){
                printf("%d\t|\t",box[i][j]);
            }else{
                printf("\t|\t");
            }
        }
    }
    printf("\n");

}

int *IndexFinder(int **box,int size){                                                  //This function is to find the empty space index values to 
    int i,j,flag = 0;                                                                  //do the puzzle operation in play
    for(i=0;i<2;i++){
        arr[i] = 0;
    }
    for(i = 0;i < size;i++){
	    if(flag == 1){
           break;
        }
        for(j = 0;j<size;j++){
            if(box[i][j] == size*size){
                arr[0] = i;
                arr[1] = j;
                flag = 1;
                break;
            }
        }
    }
    return arr;
}
