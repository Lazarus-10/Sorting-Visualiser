#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <unistd.h>

#define SIZE    250
#define width	3*SIZE + 3
#define height  3*SIZE

// current resolution 1366 X 768px, any value greater will be adjusted to max possible

using namespace std;

string comparisontext = "No. of Comparisons";
string sort_name;
int comparison_count;
vector<int> arr(SIZE);

// Function for displaying Text
void displayText(float y,string stringToDisplay, void* font , float r = 0, float g = 0, float b = 0)
{
	glColor3f(r, g, b);
    int len = stringToDisplay.length();
    int stringWidthInPixels = 0;
    // finding the width of string in pixels
    for(int i=0 ;i<len ;i++){
	    stringWidthInPixels += glutBitmapWidth(font, stringToDisplay[i]);
	}
    // choose x such that string is positioned in centre.
    float x = (width-stringWidthInPixels)/2; 
	glRasterPos2f(x, y);

	for(int i=0 ;i<len ;i++){
		glutBitmapCharacter(font, stringToDisplay[i]);
	}
    glColor3f(0.0,0.0,0.0);
}

// Display Initialization
void init()
{
	glClearColor(1.0f,1.0f,1.0f,1.0f);
}

// This Function plot the sample array
void drawbar(vector<int> arr)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	displayText(height - 27,sort_name, GLUT_BITMAP_TIMES_ROMAN_24, 1, 0, 0);
    displayText(height - 45, "--------------------------------------------------", GLUT_BITMAP_HELVETICA_18, 0,102/255.0,0);
    displayText(height - 65, "Array Size =       ", GLUT_BITMAP_HELVETICA_18, 0 ,0, 0);
    displayText(height - 65, "                        " + to_string(SIZE), GLUT_BITMAP_HELVETICA_18, 1 ,0, 0);
	displayText(height - 90,"No. of Comparisons =        ",GLUT_BITMAP_HELVETICA_18);
    displayText(height - 90,"                                        " + to_string(comparison_count),GLUT_BITMAP_HELVETICA_18, 1, 0, 0);

	glColor3f(102/255.0, 0.0, 204/255.0); // bar color: strong violet
	int x=0;
	for(int i=0; i<arr.size(); i++)
	{
		glRecti(x,0,x+2,arr[i]); // 2px wide bar
		x+=3; // left a gap of 1px
	}
	// glFlush(); // glFlush() empties all commands in buffers and forces all pending commands to be executed immediately without waiting buffers are full.
    glutSwapBuffers();
	usleep(100);
}

//Structure of Quicksort 
struct Quicksort
{
	int findpivot(vector<int> &, int,int,int);
	int partition(vector<int> &, int, int);
	void quicksort(vector<int> &, int,int);
};

//This function decide pivot for quick sort
int Quicksort::findpivot(vector<int> &sample, int left, int mid, int right)
{

	comparison_count++;
	drawbar(sample);
	if((sample[left]>=sample[mid]&&sample[left]<=sample[right])||
	  	(sample[left]<=sample[mid]&&sample[left]>=sample[right]))
		return left;

	comparison_count++;
	drawbar(sample);
	if((sample[mid]>=sample[left]&&sample[mid]<=sample[right])||
  		(sample[mid]<=sample[left]&&sample[mid]>=sample[right]))
		return mid;

	comparison_count++;
	drawbar(sample);
  	if((sample[right]>=sample[mid]&&sample[right]<=sample[left])||
		(sample[right]<=sample[mid]&&sample[right]>=sample[left]))
		return right;
		return right;
}

// This Function do partition according to pivot
int Quicksort::partition(vector<int> &sample,int left,int right)
{
	int p=findpivot(sample,left,(left+right)/2,right);
	swap(sample[left],sample[p]);
	drawbar(sample);
	p=sample[left];
	int i=left+1;
	int j=left+1;
	for(;i<=right;i++)
	{
		comparison_count++;
		if(sample[i]<p)
		{
			swap(sample[i],sample[j]);
			j++;
		}
		drawbar(sample);
	}
	swap(sample[left],sample[j-1]);
	drawbar(sample);
  return j-1;
}

/*This function divide the partitioned sample 
and again call the quicksort function reccursively*/
void Quicksort::quicksort(vector<int> &sample,int left,int right)
{
  if(right>left)
  {
    int p=partition(sample,left,right);
    quicksort(sample,left,p-1);
    quicksort(sample,p+1,right);
  }
}

struct InsertionSort{
    void insertionSort(vector<int> &);
};

void InsertionSort::insertionSort(vector<int> &sample){
    drawbar(sample);
    int i, key, j;
    int n = sample.size();
    for (i = 1; i < n; i++)
    {
        key = sample[i];
        j = i - 1;
 
        /* Move elements of sample[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && sample[j] > key)
        {
            comparison_count += 2;
            sample[j + 1] = sample[j];
            j = j - 1;
            drawbar(sample);
        }
        sample[j + 1] = key;
        drawbar(sample);
    }
}
// Struct for Selection Sort
struct SelectionSort
{
	void selectionsort(vector<int> &);
};

// Thi s Function do sorting byselecting minimum element and putting it at front
void SelectionSort::selectionsort(vector<int> &sample)  
{  
	drawbar(sample);
    int i,j,min_idx;
    int n=sample.size();  
    for (i = 0; i < n-1; i++)  
    {  
        min_idx = i;  
        for (j = i+1; j < n; j++) 
        { 
        	if (sample[j] < sample[min_idx])  
            	min_idx = j;

            comparison_count++;
            drawbar(sample);  
        }
        swap(sample[min_idx],sample[i]);
        drawbar(sample);
    }
    drawbar(sample);  
}

//Structure for bubbleSort
struct BubbleSort
{
	void bubblesort(vector<int> &);
};														


// This Function sort the sample by bubbling largest element at the right
void BubbleSort::bubblesort(vector<int> &sample) 
{ 
   drawbar(sample);
   int i, j; 
   int n = sample.size();
   bool swapped; 
   for (i = 0; i < n-1; i++) 
   { 
     swapped = false; 
     for (j = 0; j < n-i-1; j++) 
     { 
        if (sample[j] > sample[j+1]) 
        { 
           swap(sample[j], sample[j+1]); 
           swapped = true; 
        }
        comparison_count++;
        drawbar(sample); 
     } 

     if (swapped == false) 
        break; 
   }
   drawbar(sample);
}

//Structure for MergeSort
struct MergeSort
{
  void merge(vector<int> &, int, int, int);
  void mergesort(vector<int> &, int, int);
};

//This Function Merges two sorted sample comparing their value
void MergeSort::merge(vector<int> &sample, int l, int m, int r) 
{ 
	drawbar(sample);
    int i, j, k; 
    int n1 = m - l + 1;
    int n2 =  r - m; 
  
    int l_sample[n1], r_sample[n2]; 
  
    for (i = 0; i < n1; i++) 
        l_sample[i] = sample[l + i]; 
    for (j = 0; j < n2; j++) 
        r_sample[j] = sample[m + 1+ j]; 
  
    i = j = 0;
    k = l;
    while (i < n1 && j < n2) 
    { 
        if (l_sample[i] <= r_sample[j]) 
        { 
            sample[k] = l_sample[i]; 
            i++; 
        } 
        else
        { 
            sample[k] = r_sample[j]; 
            j++; 
        } 
        k++;

        comparison_count++;
        drawbar(sample);
    } 
  
    while (i < n1) 
    { 
        sample[k] = l_sample[i]; 
        i++; 
        k++;
        comparison_count++;
        drawbar(sample);
 
    } 

    while (j < n2) 
    { 
        sample[k] = r_sample[j]; 
        j++; 
        k++;
        comparison_count++;
        drawbar(sample);
 
    }
    drawbar(sample);
} 
  
// This function sort the sample by calling recursively on two halves 
//and then calling merge to merge them
void MergeSort::mergesort(vector<int> &sample, int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
  
        mergesort(sample, l, m); 
        mergesort(sample, m+1, r); 
        merge(sample, l, m, r); 
    } 
}

struct BinaryInsertionSort{
    void insertionSort(vector<int> &);
    int binarySearch(const vector<int>&, int, int, int);
};

int BinaryInsertionSort::binarySearch(const vector<int> &sample, int item, int low, int high){
     while (low <= high) {
        comparison_count++;
        int mid = low + (high - low) / 2;
        comparison_count++;
        if (item == sample[mid])
            return mid + 1;
        else if (item > sample[mid]){
            comparison_count++;
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
 
    return low;
}

void BinaryInsertionSort::insertionSort(vector<int> &sample){
    int i, loc, j, k, selected;
    int n = sample.size();
    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = sample[i];
 
        // find location where selected sould be inseretd
        loc = binarySearch(sample, selected, 0, j);
 
        // Move all elements after location to create space
        while (j >= loc) {
            sample[j + 1] = sample[j];
            j--;
            comparison_count++;
            drawbar(sample);
        }
        sample[j + 1] = selected;
        drawbar(sample);
    }
}

//This is our display funtion which call different sorting algorithms one by one
void display()
{
	vector<int> temp ;

	temp=arr;
	MergeSort my_mergesort;
	comparison_count = 0;
	sort_name = "Merge Sort";
	my_mergesort.mergesort(temp,0,temp.size()-1);
	sleep(2);

	temp=arr;
	Quicksort my_qsort;
	comparison_count = 0;
	sort_name = "Quick Sort";
	my_qsort.quicksort(temp,0,temp.size()-1);
	sleep(2);

    temp = arr;
    InsertionSort my_insertionSort;
    comparison_count = 0;
    sort_name = "Insertion Sort";
    my_insertionSort.insertionSort(temp);
    sleep(2);

    temp = arr;
    BinaryInsertionSort my_binaryInsertionSort;
    comparison_count = 0;
    sort_name = "Binary Insertion Sort";
    my_binaryInsertionSort.insertionSort(temp);
    sleep(2);

	temp=arr;
	BubbleSort my_bubsort;
	comparison_count = 0;
	sort_name = "Bubble Sort";
	my_bubsort.bubblesort(temp);
	sleep(2);


	temp=arr;
	SelectionSort my_selsort;
	comparison_count = 0;
	sort_name = "Selection Sort";
	my_selsort.selectionsort(temp);
	sleep(2);
}


int main(int argc, char **argv)
{
	srand(time(NULL));

	for(int i=0; i<SIZE; i++)
		arr[i] = rand()%(height-100);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE); // setting up the display frame buffers 
    // GLUT_RGB - Use RGB color
    // GLUT_SINGLE - allocate a single frame buffer for the display. The default.
    // GLUT_DOUBLE - allocate two frame buffers to switch between (for animation).
	glutInitWindowSize(width, height); // initializing the size of the window
    glutInitWindowPosition(0, 0); // initialising the posiiton
	glutCreateWindow("Visualization of Sorting Algorithms"); 
	gluOrtho2D(0,width,0,height); // sets up a two-dimensional orthographic viewing region.
	init();
	glutDisplayFunc(display);
	glutMainLoop(); // executes the callback functions as and when required, which in return executes the opengl commands.
}