#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;


char sudoku_grid[9][9];


bool is_valid(int checked_row, int checked_column, char numero){
    /*
    Para una casilla vacía ('.') verificar 
    si un número x se puede colocar
    */
    
    //Verificar validez de la fila
    for(int i=0;i<9;i++){
        if(sudoku_grid[checked_row][i]==numero){
            return false;
        }
    }
    
    //Verificar validez de la columna
    for(int i=0;i<9;i++){
        if(sudoku_grid[i][checked_column]==numero){
            return false;
        }
    }
    
    //Prepara límites para el bloque 3x3
    int row_inferior=(checked_row/3)*3;
    int row_superior=((checked_row/3)*3)+3;
    int column_inferior=(checked_column/3)*3;
    int column_superior=((checked_column/3)*3)+3;
    //Verificar validez de sub-bloque 3x3
    for(int i=row_inferior;i<row_superior;i++){
        for(int j=column_inferior;j<column_superior;j++){
            if(sudoku_grid[i][j]==numero){
                return false;
            }
        }
    }
    
    return true;
}

bool sudoku_solver(int row,int column){

    /*
    Si row==9, significa que se excedió de las 
    9 filas del sudoku. Entonces ya se completaron
    todas las celdas
    */
    if(row==9){
        return true;
    }
    /*
    Si column==9, se excede del número de columnas,
    entonces pasa a la siguiente fila con la columna
    en 0
    */
    if(column==9){
       return sudoku_solver(row+1,0);
    }
    
    //Si ya hay un elemento en esa celda, pasa a la siguiente
    if(sudoku_grid[row][column]!='.'){
        return sudoku_solver(row,column+1);
    }
    
    //Prueba todas las opciones válidas en las casillas vacías
    for(char cell='1';cell<='9';cell++){
        if(is_valid(row,column,cell)){
            sudoku_grid[row][column] = cell;
            if(sudoku_solver(row,column+1)){
                return true;
            }
            sudoku_grid[row][column]='.';
        }
    }
    
    return false;
}

int main()
{
    auto start = high_resolution_clock::now();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test_cases;
    string line;
    int to_int;
    
    cin>>test_cases;
    
    //Iterar por el número de casos de prueba T<=30
    for(int i=1;i<=test_cases;i++){ 
        
        for(int j=0;j<9;j++){
            cin>>line; //obtener cada una de las 9 filas del sudoku
            for(int k=0;k<9;k++){
                /*Guarda cada elemento del sudoku en una matriz*/
                sudoku_grid[j][k]=line[k];
            }
        }
        
        cout<<"Case "<<i<<":\n";
        sudoku_solver(0,0);
        for(int m=0;m<9;m++){
            for(int n=0;n<9;n++){
                cout<<sudoku_grid[m][n];
            }
            cout<<"\n";
        }
    }
        
    auto end = high_resolution_clock::now();
    auto duration=duration_cast<milliseconds>(end-start);
    cout<<"Execution time: "<<duration.count()<<" milliseconds \n";
    return 0;
}
