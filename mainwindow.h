#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_Sort_clicked();

    void InitArray(int * copyArray, int * pasteArray, int arraySize);

    int * BackupArray(int * array, int arraySize);

    void PrintArray(QTextEdit *  obj, int * array, int arraySize);

    void swap(int * n1, int * n2);

    void InsertionSort(int * array, int arraySize);

    void SelectionSort(int * array, int arraySize);

    void ShellSort(int * array, int arraySize);
        void ShellSort_InsertionSort(int * array, int start, int end, int gap);

    void BubbleSort(int * array, int arraySize);

    void QuickSort(int * array, int start, int end);
        int QuickSort_Split(int * array, int start, int end);

    void MergeSort(int * array, int start, int end, int * tmp);
        void MergeSort_Merge(int * array, int start, int mid, int end, int * tmp);

    void HeapSort(int * array, int arraySize);
        void HeapSort_Heapify(int * array, int root, int arraySize);

    void RadixSort(int * array, int arraySize);

    void on_pushButton_Set_clicked();

    void on_pushButton_Clear_clicked();

private:
    Ui::MainWindow *ui;
    int count1, count2;
};
#endif // MAINWINDOW_H
