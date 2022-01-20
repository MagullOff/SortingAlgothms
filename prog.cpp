//#define BUBBLE_SORT
//#define SELECTION_SORT
//#define INSERTION_SORT
//#define COUNT_BUCKET_SORT
//#define QUICK_SORT
//#define MERGE_SORT
#include<iostream>
#define MAX_LEN 16 
#define M 10
using namespace std;

#pragma region UTILS_AND_CLASS 
class node {
public:
    int val;
    node* next;
    node(int val = 0, node* next = nullptr) : val(val), next(next) {}
};

node* head = nullptr;
int A[MAX_LEN] = { 5,2,4,1,9,6,4,0,6,1,7,8,9,3,4,9 };

void printList(node* h) {
    node* p = h;
    while (p != nullptr) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

void printAll(node* h) {
    cout << "---------PRINTING TAB----------" << endl;
    for (int i = 0; i < MAX_LEN; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    cout << "--------PRINTING LIST----------" << endl;
    printList(h);
    cout << "---------END OF PRINT----------" << endl << endl;
}

void pushBack(node** h, node* newP) {
    node* p = *h;
    if (!p) {
        head = newP;
        return;
    }
    while (p->next)
        p = p->next;
    p->next = newP;
}
#pragma endregion

#pragma region BUBBLE_SORT
void bubbleSort_tab() {
    for (int i = 0; i < MAX_LEN; i++)
        for (int j = 0; j < MAX_LEN - i - 1; j++)
            if (A[j] > A[j + 1])
                swap(A[j], A[j + 1]);
}

void bubbleSort_list() {
    node* end = nullptr;
    node* p = head;
    node* pprev = nullptr;
    if(p->next != nullptr)
        while (end != head) {
            if (p->next == end || p->next == nullptr) {
                end = p;
                p = head;
                pprev = nullptr;
                continue;
            }

            if (p->val > p->next->val) {
                if (p == head) {
                    // using pprev as an assisting variable
                    pprev = p->next;
                    p->next = p->next->next;
                    pprev->next = p;
                    p = pprev;
                    head = p;
                }
                else {
                    pprev->next = p->next;
                    p->next = pprev->next->next;
                    pprev->next->next = p;
                    p = pprev->next;
                }
            }
            pprev = p;
            p = p->next;
            //printList(head);
        }
}
#pragma endregion

#pragma region SELECTION_SORT
void selectionSort_list() {
    node* headS = nullptr;
    while (head) {
        node* pMax = head;
        node* ppMax = nullptr;
        node* p = head;
        while (p->next) {
            if (p->next->val >= pMax->val) {
                ppMax = p;
                pMax = p->next;
            }
            p = p->next;
        }
        if (ppMax) ppMax->next = pMax->next;
        else head = head->next;
        pMax->next = headS;
        headS = pMax;
    }
    head = headS;
}

void selectionSort_tab() {
    for (int i = 0; i < MAX_LEN; i++) {
        int iMin = i;
        for (int j = i; j < MAX_LEN; j++)
            if (A[j] < A[iMin]) iMin = j;
        swap(A[i], A[iMin]);
    }
}
#pragma endregion

#pragma region INSERTION_SORT
void insertionSort_list() {
    node* headS = nullptr;
    while (head) {
        node* p = head;
        head = head->next;
        p->next = nullptr;
        if (!headS || headS->val > p->val) {
            p->next = headS;
            headS = p;
        }
        else {
            node* pIter = headS;
            while (pIter->next && pIter->next->val < p->val)
                pIter = pIter->next;
            p->next = pIter->next;
            pIter->next = p;
        }
    }
    head = headS;
}

void insertionSort_tab() {
    for (int i = 1; i < MAX_LEN; i++) {
        int k = A[i];
        int j = i;
        while (j > 0 && A[j - 1] > k) {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = k;
    }
}
#pragma endregion

#pragma region COUNT_BUCKET_SORT
void countSort_simple() {
    int count[M] = { 0 };
    for (int i = 0; i < MAX_LEN; i++)
        count[A[i]]++;
    int iter = 0;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < count[i]; j++)
            A[iter++] = i;
}

void bucketSort() {
    node* bucket[M];
    for (int i = 0; i < M; i++)
        bucket[i] = nullptr;

    while (head) {
        node* p = head;
        head = head->next;
        p->next = nullptr;
        if (!bucket[p->val]) bucket[p->val] = p;
        else {
            p->next = bucket[p->val];
            bucket[p->val] = p;
        }
    }

    for (int i = 0; i < M; i++) {
        while (bucket[i]) {
            node* p = bucket[i];
            bucket[i] = bucket[i]->next;
            p->next = nullptr;
            p->next = head;
            head = p;
        }
    }
}
#pragma endregion

#pragma region QUICK_SORT
int partition_tab(int low, int high) {
    int pivot = A[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);
    return i + 1;
}

void quickSort_tab(int low = 0, int high = MAX_LEN - 1) {
    if (low < high) {
        int pi = partition_tab(low, high);
        quickSort_tab(low, pi - 1);
        quickSort_tab(pi, high);
    }
}

void quickSort_list(node*& h, node*& t) {
    if (!h || !t || h->next == nullptr) return;
    int pivot = h->val;
    node* headM = nullptr;
    node* tailM = nullptr;
    node* headW = nullptr;
    node* tailW = nullptr;
    node* headR = nullptr;
    node* tailR = nullptr;

    while (h) {
        node* p = h;
        h = h->next;
        p->next = nullptr;

        if (p->val < pivot) {
            tailM == nullptr ? headM = p : tailM->next = p;
            tailM = p;
        }
        if (p->val > pivot) {
            tailW == nullptr ? headW = p : tailW->next = p;
            tailW = p;
        }
        if (p->val == pivot) {
            tailR == nullptr ? headR = p : tailR->next = p;
            tailR = p;
        }
    }

    quickSort_list(headM, tailM);
    quickSort_list(headW, tailW);

    if (headM) {
        h = headM;
        tailM->next = headR;
    }
    else h = headR;

    if (tailW) {
        t = tailW;
        tailR->next = headW;
    }
    else t = tailR;
}
#pragma endregion

#pragma region MERGE
void merge_tab(int l, int m, int p) {
    int* arr = new int[p - l + 1];
    //int arr[p - l + 1];
    int iter = 0;
    int iterL = l;
    int iterR = m + 1;
    while (iterL <= m && iterR <= p) {
        if (A[iterL] <= A[iterR])
            arr[iter++] = A[iterL++];
        else
            arr[iter++] = A[iterR++];
    }
    while (iterL <= m)
        arr[iter++] = A[iterL++];
    while (iterR <= p)
        arr[iter++] = A[iterR++];

    for (int i = l; i <= p; i++) {
        A[i] = arr[i - l];
    }
    delete[] arr;
}

node* merge_list(node* head1, node* head2) {
    node* headNew = nullptr;
    node* tailNew = nullptr;
    while (head1 && head2) {
        node* p;
        if (head1->val <= head2->val) {
            p = head1;
            head1 = head1->next;
        }
        else {
            p = head2;
            head2 = head2->next;
        }
        if (!headNew) headNew = p;
        else tailNew->next = p;
        tailNew = p;
    }
    while (head1) {
        node* p = head1;
        head1 = head1->next;
        p->next = nullptr;
        tailNew->next = p;
        tailNew = p;
    }
    while (head2) {
        node* p = head2;
        head2 = head2->next;
        p->next = nullptr;
        tailNew->next = p;
        tailNew = p;
    }

    return headNew;
}
#pragma endregion

#pragma region MERGE_SORT
void mergeSort_tab(int l = 0, int r = MAX_LEN - 1) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort_tab(l, m);
    mergeSort_tab(m + 1, r);
    merge_tab(l, m, r);
}

void mergeSort_list() {
    node* sArr[MAX_LEN];
    int iLast = -1;
    node* pLast = nullptr;
    while (head) {
        node* p = head;
        head = head->next;
        p->next = nullptr;
        if (!pLast || p->val < pLast->val)
            sArr[++iLast] = p;
        else
            pLast->next = p;
        pLast = p;
    }

    while (iLast > 0) {
        int i = -2;
        while (i < iLast - 1) {
            i += 2;
            sArr[i / 2] = merge_list(sArr[i], sArr[i + 1]);
        }
        iLast = i / 2;
    }
    head = sArr[0];
}
#pragma endregion

#pragma region MAIN
int main() {
    // init list
    node* tail;
    cout << "ORIGINAL STATE" << endl;
    for (int i = 0; i < MAX_LEN; i++) {
        node* p = new node(A[i], nullptr);
        pushBack(&head, p);
        if (i == MAX_LEN - 1) tail = p;
    }
    printAll(head);

#ifdef BUBBLE_SORT//simple count sort/bucket sort
    cout << "PERFORMING BUBBLE SORT" << endl;
    bubbleSort_tab();
    bubbleSort_list();
#endif

#ifdef COUNT_BUCKET_SORT//simple count sort/bucket sort
    cout << "PERFORMING COUNT/BUCKET SORT" << endl;
    countSort_simple();
    bucketSort();
#endif

#ifdef INSERTION_SORT//insertion sort
    cout << "PERFORMING INSERTION SORT" << endl;
    insertionSort_list();
    insertionSort_tab();
#endif

#ifdef SELECTION_SORT// selection sort    
    cout << "PERFORMING SELECTION SORT" << endl;
    selectionSort_list();
    selectionSort_tab();
#endif

#ifdef QUICK_SORT
    cout << "PERFORMING QUICKSORT" << endl;
    quickSort_tab();
    quickSort_list(head, tail);
#endif

#ifdef MERGE_SORT
    cout << "PERFORMING MERGESORT" << endl;
    mergeSort_tab();
    mergeSort_list();
#endif
    //printing
    printAll(head);
}
#pragma endregion