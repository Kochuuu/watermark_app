# Watermark app
Application for automatically adding a watermark to an image file. The project was created for the purpose of obtaining an engineering degree.

The application is used to automatically give a watermark to a graphic file. The program accepts any number of photos from the computer's memory, then scans them selecting the most advantageous place among all the corners of the photo and the center at the bottom. The program scans the differences of the RGB components of each pixel, and sums them up creating tables of deviations. The application selects the place with the least deviation. The program allows you to save all photos, and optionally view them with detailed data. The saved photo in memory has the name of the original file with the annotation "_marked".

The application uses the QT framework.
