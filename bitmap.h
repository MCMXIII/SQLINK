#ifndef Bitmap_H
#define Bitmap_H

	typedef struct {
		int m_numOfFeatures;
		int* m_featuresArray;
	} Bitmap;
	Bitmap* createBitmap(int numOfFeatures);
	Bitmap* destroyBitmap(Bitmap* b);
	int turnOn(Bitmap * b, int bit);
	int turnOff(Bitmap * b, int bit);
	int changeBit(Bitmap * b, int bit);
	int bitStatus(Bitmap * b, int bit);
	int printBitmap(Bitmap * b);
	int printBitmap2(Bitmap * b);

#endif
