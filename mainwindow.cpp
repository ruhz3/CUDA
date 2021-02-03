#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QQueue>
#include <cmath>
#include <QElapsedTimer>
#include <time.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitArray(int * copyArray, int * pasteArray, int arraySize)
{
    for(int i = 0; i < arraySize; i++)
        pasteArray[i] = copyArray[i];
}

int * MainWindow::BackupArray(int * array, int arraySize)
{
    int * backupArray = new int[arraySize];
    for(int i = 0; i < arraySize; i++)
        backupArray[i] = array[i];

    return backupArray;
}

void MainWindow::PrintArray(QTextEdit * obj, int * array, int arraySize)
{
    QString PrintString;
    for(int i = 0; i< arraySize; i++)
        PrintString += (QString::number(array[i]) + " ");
    obj->setText(PrintString);
}

void MainWindow::swap(int * n1, int * n2)
{
    int tmp;

    tmp = * n1;
    * n1 = * n2;
    *n2 = tmp;
}


void MainWindow::InsertionSort(int * array, int arraySize)
{
    int index, search;
    int tmp;

    for (index = 1; index < arraySize; index++)
    {
        tmp = array[index];
        for (search = index - 1; (search >= 0) && (tmp < array[search]); search--)
            array[search + 1] = array[search];
        array[search + 1] = tmp;
    }
}

void MainWindow::ShellSort(int * array, int arraySize)
{
    int i, gap;

    for(gap=arraySize/2; gap>0; gap=(gap-1)/3)
    {
        for(i=0; i<gap; i++)
            ShellSort_InsertionSort(array, i, arraySize-1, gap);
    }
}

void MainWindow::ShellSort_InsertionSort(int * array, int start, int end, int gap)
{
    int i, j, key;

    for(i=start+gap; i<=end; i=i+gap)
    {
      key = array[i];
      for(j=i-gap; j>=start && array[j]>key; j=j-gap)
        array[j+gap] = array[j];
      array[j+gap] = key;
    }
}

void MainWindow::BubbleSort(int * array, int arraySize)
{
    for(int loop = 0; loop < arraySize; loop++)
    {
        for(int search = 0; search < arraySize - (loop + 1); search++)
        {
           if(array[search] > array[search+1])
               swap(&array[search], &array[search+1]);
        }
    }
}



void MainWindow::QuickSort(int * array, int left, int right)
{
    if(left >= right)
        return;


    int splitIndex = QuickSort_Split(array, left, right);
    QuickSort(array, left, splitIndex-1);
    QuickSort(array, splitIndex + 1, right);
}


int MainWindow::QuickSort_Split(int * array, int left, int right)
{
    int pivot = array[left];
    int i = left, j = right;
    while (i < j)
    {
        while (pivot < array[j]) { j--; }
        while (i < j && pivot >= array[i]) { i++; }
        swap(&array[i], &array[j]);
    }
    array[left] = array[i];
    array[i] = pivot;

    return i;
}

void MainWindow::MergeSort(int * array, int start, int end, int * tmp)
{
    if(start >= end)
        return;

    int splitPoint = (start + end) / 2;
    MergeSort(array, start, splitPoint, tmp);
    MergeSort(array, splitPoint + 1, end, tmp);
    MergeSort_Merge(array, start, splitPoint, end, tmp);
}

void MainWindow::MergeSort_Merge(int * array, int start, int splitPoint, int end, int * tmp)
{
    int leftIndex = start;
    int rightIndex = splitPoint + 1;
    int tmpIndex = start;

    while(leftIndex <= splitPoint && rightIndex <= end)
    {
        if(array[leftIndex] <= array[rightIndex])
            tmp[tmpIndex++] = array[leftIndex++];
        else
            tmp[tmpIndex++] = array[rightIndex++];
    }

    while(leftIndex <= splitPoint)
        tmp[tmpIndex++] = array[leftIndex++];

    while(rightIndex <= end)
        tmp[tmpIndex++] = array[rightIndex++];

    for(int i = start; i <= end; i++)
    {
        array[i] = tmp[i];
    }
}

void MainWindow::SelectionSort(int * array, int arraySize)
{
    int minSearch;

    for(int i = 0; i < arraySize-1; i++ )
    {
        minSearch = i;
        for(int j = i + 1 ; j < arraySize; j++ )
            if(array[minSearch] > array[ j ] )
                minSearch = j;
        swap(&array[i], &array[minSearch]);
    }
}

void MainWindow::HeapSort(int * array, int arraySize)
{
    for(int i = arraySize/2; i >= 0; i--)
        HeapSort_Heapify(array, i, arraySize);

    for(int j = arraySize-1; j > 0; j--)
    {
        swap(&array[0], &array[j]);
        HeapSort_Heapify(array, 0, j);
    }
}

void MainWindow::HeapSort_Heapify(int * array, int k, int arraySize)
{
    int leftIndex = 2*k;
    int rightIndex = 2*k + 1;
    int bigger;

    if(rightIndex < arraySize)
    {
        if(array[leftIndex] > array[rightIndex])
            bigger = leftIndex;
        else
            bigger = rightIndex;
    }
    else if(leftIndex < arraySize)
        bigger = leftIndex;
    else
        return;

    if(array[bigger] > array[k])
    {
        swap(&array[k], &array[bigger]);
        HeapSort_Heapify(array, bigger, arraySize);
    }
}



void MainWindow::RadixSort(int * array, int arraySize)
{
    QQueue<int> * bucket = new QQueue<int>[10];
    int max = 1;

    for(int i = 0; i < arraySize; i++)
        if((int)(log10(array[i])) + 1 > max)
            max = (int)(log10(array[i])) + 1;

    for(int i = 1, pow = 1; i <= max; i++, pow *=10)
    {
        for(int j = 0; j < arraySize; j++)
           bucket[array[j]/pow%10].enqueue(array[j]);

        for(int k = 0, index = 0; k < 10; k++)
           for(int a = 0; (a < bucket[k].length()), (bucket[k].empty()!= true); a++)
           {
               array[index] = bucket[k].dequeue();
               index++;
           }
    }
}

void MainWindow::on_pushButton_Sort_clicked()
{
    QElapsedTimer t;
    QString InputString = ui->lineEdit_Input->text();
    QStringList InputStringList = InputString.split(" ");

    int * inputArray = new int[InputStringList.length()];
    int arraySize = InputStringList.length();

    for(int i = 0; i < arraySize; i++)
        inputArray[i] = InputStringList[i].toInt();

    int * backupArray = new int[InputStringList.length()];
    InitArray(inputArray, backupArray, arraySize);
    int * not_In_Place = new int[InputStringList.length()];

    ui->textEdit_Status->append("Input Array Converted!");
    ui->textEdit_Status->append("Array Size : " + QString::number(arraySize) + "\n");

    InputString = QString();
    for(int j = 0; j < arraySize; j++)
        InputString += QString::number(inputArray[j]) + " ";
    ui->textEdit_Status->append(InputString);



    ui->textEdit_Status->append("\nInsertion Sort...");
    t.start();
    InsertionSort(inputArray, arraySize);
    ui->textEdit_Status->append("Finished! (" + QString::number(t.nsecsElapsed()) + "ns)\n");
    PrintArray(ui->textEdit_Insertion, inputArray, arraySize);
    InitArray(backupArray, inputArray, arraySize);

    ui->textEdit_Status->append("Shell Sort...");
    t.restart();
    ShellSort(inputArray, arraySize);
    ui->textEdit_Status->append("Finished! (" + QString::number(t.nsecsElapsed()) + "ns)\n");
    PrintArray(ui->textEdit_Shell, inputArray, arraySize);
    InitArray(backupArray, inputArray, arraySize);

    ui->textEdit_Status->append("Bubble Sort...");
    t.restart();
    BubbleSort(inputArray, arraySize);
    ui->textEdit_Status->append("Finished! (" + QString::number(t.nsecsElapsed()) + "ns)\n");
    PrintArray(ui->textEdit_Bubble, inputArray, arraySize);
    InitArray(backupArray, inputArray, arraySize);

    ui->textEdit_Status->append("Quick Sort...");
    t.restart();
    QuickSort(inputArray, 0, arraySize-1);
    ui->textEdit_Status->append("Finished! (" + QString::number(t.nsecsElapsed()) + "ns)\n");
    PrintArray(ui->textEdit_Quick, inputArray, arraySize);
    InitArray(backupArray, inputArray, arraySize);

    ui->textEdit_Status->append("Merge Sort...");
    t.restart();
    MergeSort(inputArray, 0, arraySize-1, not_In_Place);
    ui->textEdit_Status->append("Finished! (" + QString::number(t.nsecsElapsed()) + "ns)\n");
    PrintArray(ui->textEdit_Merge, inputArray, arraySize);
    InitArray(backupArray, inputArray, arraySize);

    ui->textEdit_Status->append("Selection Sort...");
    t.restart();
    SelectionSort(inputArray, arraySize);
    ui->textEdit_Status->append("Finished! (" + QString::number(t.nsecsElapsed()) + "ns)\n");
    PrintArray(ui->textEdit_Selection, inputArray, arraySize);
    InitArray(backupArray, inputArray, arraySize);

    ui->textEdit_Status->append("Heap Sort...");
    HeapSort(inputArray, arraySize);
    ui->textEdit_Status->append("Finished! (" + QString::number(t.nsecsElapsed()) + "ns)\n");
    PrintArray(ui->textEdit_Heap, inputArray, arraySize);
    InitArray(backupArray, inputArray, arraySize);

    ui->textEdit_Status->append("Radix Sort...");
    t.restart();
    RadixSort(inputArray, arraySize);
    ui->textEdit_Status->append("Finished! (" + QString::number(t.nsecsElapsed()) + "ns)\n");
    PrintArray(ui->textEdit_Radix, inputArray, arraySize);
    InitArray(backupArray, inputArray, arraySize);

    ui->pushButton_Sort->setEnabled(false);

}

void MainWindow::on_pushButton_Set_clicked()
{
    QString From = ui->lineEdit_Random_From->text();
    QString To = ui->lineEdit_Random_To->text();
    QString Size = ui->lineEdit_Random_Size->text();
    QString RandomInput;

    int from = From.toInt();
    int to = To.toInt();
    int size = Size.toInt();

    qsrand(0);
    for(int i = 0; i < size - 1; i++)
        RandomInput += QString::number(qrand()%(to - from + 1) + from) + " ";
    RandomInput += QString::number(rand()%(to - from + 1) + from);

    ui->textEdit_Status->append("Random Input generated!\n");
    ui->textEdit_Status->append("(Size : " + QString::number(size) + "/ Range : " + QString::number(from) + " ~ " + QString::number(to) +")\n");
    ui->lineEdit_Input->setText(RandomInput);
}


void MainWindow::on_pushButton_Clear_clicked()
{
    ui->lineEdit_Input->setText("");
    ui->lineEdit_Random_To->setText("");
    ui->lineEdit_Random_From->setText("");
    ui->lineEdit_Random_Size->setText("");
    ui->textEdit_Insertion->setText("");
    ui->textEdit_Shell->setText("");
    ui->textEdit_Bubble->setText("");
    ui->textEdit_Quick->setText("");
    ui->textEdit_Merge->setText("");
    ui->textEdit_Selection->setText("");
    ui->textEdit_Heap->setText("");
    ui->textEdit_Radix->setText("");
    ui->textEdit_Status->append("All Text Cleared!\n");

    ui->pushButton_Sort->setEnabled(true);
}
