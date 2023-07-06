﻿#include "Sort.h"

Sort::Sort(unsigned size, unsigned maxvalue, int xcoord, int ycoord, float xscale, float yscale)
{
	this->arr_size = size;
	this->arr = std::vector<int>(arr_size);
	for (int i = 0; i < arr_size; i++)
	{
		this->arr[i] = rand() % maxvalue;
	}
	this->n = arr.size() - 1;
	this->max_value = maxvalue;
	this->x = xcoord;
	this->y = ycoord;
	this->x_scale = xscale;
	this->y_scale = yscale;
	this->i = 1;
	this->operation_counter = 0;

	BubbleSort bubble;
	MergeSort merge;
	HeapSort heap(this->arr_size);
	QuickSort quick(this->arr);
	this->quick = quick;
	this->heap = heap;
}

void Sort::reshuffleArray()
{
	for (int i = 0; i < arr_size; i++)
	{
		this->arr[i] = rand() % max_value;
	}

	this->n = arr_size - 1;
	this->operation_counter = 0;
	this->i = 1;

	merge.rebuild();
	heap.rebuild(this->arr_size);
	quick.rebuild(this->arr);
}

bool Sort::tick(SortingAlg alg)
{
	if (std::is_sorted(arr.begin(), arr.end()))
		return false;

	switch (alg)
	{
	case SortingAlg::BUBBLE:
		return bubble.tick(arr, i, n, operation_counter);
		break;
	case SortingAlg::MERGE:
		return merge.tick(arr, i, operation_counter);
		break;
	case SortingAlg::HEAP:
		return heap.tick(arr, i, n, operation_counter);
		break;
	case SortingAlg::QUICK:
		return quick.tick(arr, i, operation_counter);
		break;
	default:
		return true;
	}
	return true;
}

void Sort::drawArray()
{
    // Add labels
    glColor3f(1, 1, 1);
    glRasterPos2f(this->x + 20, this->y - 20);
    drawString("Array Index");

    glRasterPos2f(this->x + 30, this->y + (this->y_scale * max_value) - 5);
    drawString("Array Element Value");

    // Draw all array elements with color gradient
    for (unsigned j = 0; j < arr.size(); j++)
    {
        float colorScale = ((float)arr[j] / max_value); // Scale the color based on element value

        // Change color based on the value
        float red = (arr[j] >= max_value * 0.8) ? 1.0f : colorScale;
        float green = 0.0f + colorScale;
        float blue = colorScale;

        glColor3f(0, green, 0); // Use the modified color gradient

        glRectf(
            this->x + (this->x_scale * j * 6) + 1,
            this->y + 1,
            this->x + 3 + (this->x_scale * j * 6) - 1,
            this->y + this->y_scale * arr[j] - 1);
    }

    // Add animation for current iteration
    glColor3f(1, 0, 0); // Use red color for the pointer

    glRectf(
        this->x + (this->x_scale * this->i * 6) + 1,
        this->y + 1,
        this->x + 3 + (this->x_scale * this->i * 6) - 1,
        this->y + this->y_scale * arr[this->i] - 1);
}

void Sort::drawString(const std::string &str)
{
	for (char c : str)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); // Use TIMES_ROMAN_24 font
	}
}

int Sort::getOperationCounter()
{
	return this->operation_counter;
}

int Sort::getArraySize()
{
	return this->arr.size();
}