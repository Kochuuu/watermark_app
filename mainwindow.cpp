#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "photos.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnLoad_clicked() {
  clearLbl();

  logo.load("C:\\Users\\kochm\\OneDrive\\Pulpit\\Zdjęcia "
            "Inżynierka\\Loga\\czarne z tłem(2).png");

  watermarkCoordinatesList.clear();
  imageList.clear();
  nameList.clear();

  QFileDialog dialog(nullptr, "Open File", "", "Images(*.bmp *.jpg *.png)");
  dialog.setFileMode(QFileDialog::ExistingFiles);
  QStringList fileNames;

  if (dialog.exec()) {
    fileNames = dialog.selectedFiles();
    QStringList files(fileNames);

    for (int i = 0; i < files.size(); i++) {
      QFileInfo fi(files.at(i));
      nameList.push_back(fi.baseName());
      imageList.push_back(QImage(files.at(i)));
    }
  }

  num = 0;

  if (imageList.size() > 0) {
    int NextWidth = ui->lblPicNext->width();
    int NextHeight = ui->lblPicNext->height();
    ui->lblPicNext->setPixmap(QPixmap::fromImage(
        imageList.value(num + 1).scaledToWidth(NextWidth).scaledToHeight(
            NextHeight)));
  }

  for (int i = 0; i < imageList.size(); i++)
    scanImage(imageList.at(i));

  for (int i = 0; i < imageList.size(); i++)
    markImage(i);

  if (ui->checkBoxInfo->isChecked())
    updateInfo();

  int MainWidth = ui->lblPicMain->width();
  int MainHeight = ui->lblPicMain->height();
  ui->lblPicMain->setPixmap(QPixmap::fromImage(
      imageList.value(num).scaledToWidth(MainWidth).scaledToHeight(
          MainHeight)));
}

void MainWindow::clearLbl() {
  int MainWidth = ui->lblPicMain->width();
  int PrevWidth = ui->lblPicPrev->width();
  int NextWidth = ui->lblPicNext->width();

  ui->lblPicMain->setPixmap(
      QPixmap::fromImage(picClear.scaledToWidth(MainWidth)));
  ui->lblPicPrev->setPixmap(
      QPixmap::fromImage(picClear.scaledToWidth(PrevWidth)));
  ui->lblPicNext->setPixmap(
      QPixmap::fromImage(picClear.scaledToWidth(NextWidth)));
  ui->lblInfo->setText("");
}

void MainWindow::getInfo(QImage image) {
  QString name = nameList[num];

  infoText = "Nazwa: " + name + "\nWymiary: " + QString::number(image.width()) +
             "x" + QString::number(image.height()) + "\nProponowane miejsce: ";
  int tmpNum = 0;
  if (num > 0)
    for (int i = 0; i < num; i++)
      tmpNum += 2;

  infoText += QString::number(watermarkCoordinatesList.value(tmpNum)) + "," +
              QString::number(watermarkCoordinatesList.value(tmpNum + 1));
}

void MainWindow::updateInfo() {
  if (imageList.empty() == false)
    getInfo(imageList[num]);
  ui->lblInfo->setText(infoText);
}

void MainWindow::on_btnPrevPic_clicked() {
  if (num > 0) {
    int MainWidth = ui->lblPicMain->width();
    int MainHeight = ui->lblPicMain->height();
    ui->lblPicMain->setPixmap(QPixmap::fromImage(
        imageList.value(num - 1).scaledToWidth(MainWidth).scaledToHeight(
            MainHeight)));

    int NextWidth = ui->lblPicNext->width();
    int NextHeight = ui->lblPicNext->height();
    ui->lblPicNext->setPixmap(QPixmap::fromImage(
        imageList.value(num).scaledToWidth(NextWidth).scaledToHeight(
            NextHeight)));

    int PrevWidth = ui->lblPicPrev->width();
    int PrevHeight = ui->lblPicPrev->height();
    ui->lblPicPrev->setPixmap(QPixmap::fromImage(
        imageList.value(num - 2).scaledToWidth(PrevWidth).scaledToHeight(
            PrevHeight)));
    num--;
  } else if (num == 1) {
    int MainWidth = ui->lblPicMain->width();
    int MainHeight = ui->lblPicMain->height();
    ui->lblPicMain->setPixmap(QPixmap::fromImage(
        imageList.value(num - 1).scaledToWidth(MainWidth).scaledToHeight(
            MainHeight)));

    int NextWidth = ui->lblPicNext->width();
    int NextHeight = ui->lblPicNext->height();
    ui->lblPicNext->setPixmap(QPixmap::fromImage(
        imageList.value(num).scaledToWidth(NextWidth).scaledToHeight(
            NextHeight)));

    int PrevWidth = ui->lblPicPrev->width();
    int PrevHeight = ui->lblPicPrev->height();
    ui->lblPicPrev->setPixmap(QPixmap::fromImage(
        picClear.scaledToWidth(PrevWidth).scaledToHeight(PrevHeight)));
    num--;
  }

  if (ui->checkBoxInfo->isChecked())
    updateInfo();
}

void MainWindow::on_btnNextPic_clicked() {
  if (num < imageList.size() - 1) {
    int MainWidth = ui->lblPicMain->width();
    int MainHeight = ui->lblPicMain->height();
    ui->lblPicMain->setPixmap(QPixmap::fromImage(
        imageList.value(num + 1).scaledToWidth(MainWidth).scaledToHeight(
            MainHeight)));

    int NextWidth = ui->lblPicNext->width();
    int NextHeight = ui->lblPicNext->height();
    ui->lblPicNext->setPixmap(QPixmap::fromImage(
        imageList.value(num + 2).scaledToWidth(NextWidth).scaledToHeight(
            NextHeight)));

    int PrevWidth = ui->lblPicPrev->width();
    int PrevHeight = ui->lblPicPrev->height();
    ui->lblPicPrev->setPixmap(QPixmap::fromImage(
        imageList.value(num).scaledToWidth(PrevWidth).scaledToHeight(
            PrevHeight)));
    num++;
  } else if (num == imageList.size() - 2) {
    int MainWidth = ui->lblPicMain->width();
    int MainHeight = ui->lblPicMain->height();
    ui->lblPicMain->setPixmap(QPixmap::fromImage(
        imageList.value(num - 1).scaledToWidth(MainWidth).scaledToHeight(
            MainHeight)));

    int NextWidth = ui->lblPicNext->width();
    int NextHeight = ui->lblPicNext->height();
    ui->lblPicNext->setPixmap(QPixmap::fromImage(
        imageList.value(num).scaledToWidth(NextWidth).scaledToHeight(
            NextHeight)));

    int PrevWidth = ui->lblPicPrev->width();
    int PrevHeight = ui->lblPicPrev->height();
    ui->lblPicPrev->setPixmap(QPixmap::fromImage(
        picClear.scaledToWidth(PrevWidth).scaledToHeight(PrevHeight)));
    num++;
  }

  if (ui->checkBoxInfo->isChecked())
    updateInfo();
}

void MainWindow::on_checkBoxInfo_stateChanged(int arg1) {
  if (ui->checkBoxInfo->isChecked())
    updateInfo();
  else
    ui->lblInfo->setText("");
}

void MainWindow::scanImage(QImage image) {

  rgbSearchList.clear();

  int tmpR = 0;
  int tmpG = 0;
  int tmpB = 0;

  int devR = 0;
  int devG = 0;
  int devB = 0;

  int tmpDev = 0;

  int tmpNum = 0;

  QColor tmpColor;

  deviationList.clear();

  for (int i = 0; i < image.width(); i++) {
    for (int j = 0; j < image.height() / 2; j++) {
      tmpColor = image.pixelColor(i, j).toRgb();

      if (i < image.width() / 5 &&
          j < image.height() / 5) // sprawdzenie pozycji 1
      {
        tmpR += tmpColor.red();
        tmpG += tmpColor.green();
        tmpB += tmpColor.blue();

        tmpNum++;
      } else if (i == (image.width() / 5) + 1 && j == 0) {
        rgbSearchList.push_back(tmpR / tmpNum);
        rgbSearchList.push_back(tmpG / tmpNum);
        rgbSearchList.push_back(tmpB / tmpNum);

        tmpR = 0;
        tmpG = 0;
        tmpB = 0;

        tmpNum = 0;
      }

      if (i > (image.width() / 5) * 4 &&
          j < image.height() / 5) // sprawdzenie pozycji 2
      {
        tmpR += tmpColor.red();
        tmpG += tmpColor.green();
        tmpB += tmpColor.blue();

        tmpNum++;
      } else if (i == image.width() - 1 && j == image.height() / 5) {
        rgbSearchList.push_back(tmpR / tmpNum);
        rgbSearchList.push_back(tmpG / tmpNum);
        rgbSearchList.push_back(tmpB / tmpNum);

        tmpR = 0;
        tmpG = 0;
        tmpB = 0;

        tmpNum = 0;
      }
    }
  }
  for (int i = 0; i < image.width(); i++) {
    for (int j = (image.height() / 2) + 1; j < image.height(); j++) {
      tmpColor = image.pixelColor(i, j).toRgb();

      if (i < image.width() / 5 &&
          j > (image.height() / 5) * 4) // sprawdzenie pozycji 3
      {
        tmpR += tmpColor.red();
        tmpG += tmpColor.green();
        tmpB += tmpColor.blue();

        tmpNum++;
      } else if (i == image.width() / 5 && j == (image.height() / 5) * 4) {

        rgbSearchList.push_back(tmpR / tmpNum);
        rgbSearchList.push_back(tmpG / tmpNum);
        rgbSearchList.push_back(tmpB / tmpNum);

        tmpR = 0;
        tmpG = 0;
        tmpB = 0;

        tmpNum = 0;
      }

      if ((i > (image.width() / 5) * 2 && i < (image.width() / 5) * 3) &&
          j < (image.height() / 5) * 4) // sprawdzenie pozycji 4
      {
        tmpR += tmpColor.red();
        tmpG += tmpColor.green();
        tmpB += tmpColor.blue();

        tmpNum++;
      } else if (i == ((image.width() / 5) * 3) + 1 &&
                 j == image.height() - 1) {
        rgbSearchList.push_back(tmpR / tmpNum);
        rgbSearchList.push_back(tmpG / tmpNum);
        rgbSearchList.push_back(tmpB / tmpNum);

        tmpR = 0;
        tmpG = 0;
        tmpB = 0;

        tmpNum = 0;
      }

      if ((i > (image.width() / 5) * 4 && i != image.width() - 1) &&
          (j > (image.height() / 5) * 4 &&
           j != image.height() - 1)) // sprawdzenie pozycji 5
      {
        tmpR += tmpColor.red();
        tmpG += tmpColor.green();
        tmpB += tmpColor.blue();

        tmpNum++;

      } else if (i == image.width() - 1 && j == image.height() - 1) {
        rgbSearchList.push_back(tmpR / tmpNum);
        rgbSearchList.push_back(tmpG / tmpNum);
        rgbSearchList.push_back(tmpB / tmpNum);

        tmpR = 0;
        tmpG = 0;
        tmpB = 0;

        tmpNum = 0;
      }
    }
  }

  for (int i = 0; i < image.width(); i++) {
    for (int j = 0; j < image.height() / 2; j++) {
      tmpColor = image.pixelColor(i, j).toRgb();

      if (i < image.width() / 5 &&
          j < image.height() / 5) // sprawdzenie pozycji 1
      {
        devR = tmpColor.red();
        devG = tmpColor.green();
        devB = tmpColor.blue();

      } else if (i == (image.width() / 5) + 1 && j == 0) {

        if (rgbSearchList.value(0) > devR) {
          tmpDev += rgbSearchList.value(0) - devR;
        } else
          tmpDev += devR - rgbSearchList.value(0);

        if (rgbSearchList.value(1) > devG) {
          tmpDev += rgbSearchList.value(1) - devG;
        } else
          tmpDev += devG - rgbSearchList.value(1);

        if (rgbSearchList.value(2) > devB) {
          tmpDev += rgbSearchList.value(2) - devB;
        } else
          tmpDev += devB - rgbSearchList.value(2);

        devR = 0;
        devG = 0;
        devB = 0;

        deviationList.push_back(tmpDev);
        tmpDev = 0;
      }

      if (i > (image.width() / 5) * 4 &&
          j < image.height() / 5) // sprawdzenie pozycji 2
      {
        devR = tmpColor.red();
        devG = tmpColor.green();
        devB = tmpColor.blue();
      } else if (i == image.width() - 1 && j == image.height() / 5) {
        if (rgbSearchList.value(3) > devR) {
          tmpDev += rgbSearchList.value(3) - devR;
        } else
          tmpDev += devR - rgbSearchList.value(3);

        if (rgbSearchList.value(4) > devG) {
          tmpDev += rgbSearchList.value(4) - devG;
        } else
          tmpDev += devG - rgbSearchList.value(4);

        if (rgbSearchList.value(5) > devB) {
          tmpDev += rgbSearchList.value(5) - devB;
        } else
          tmpDev += devB - rgbSearchList.value(5);

        devR = 0;
        devG = 0;
        devB = 0;

        deviationList.push_back(tmpDev);
        tmpDev = 0;
      }
    }
  }
  for (int i = 0; i < image.width(); i++) {
    for (int j = (image.height() / 2) + 1; j < image.height(); j++) {
      tmpColor = image.pixelColor(i, j).toRgb();

      if (i < image.width() / 5 &&
          j > (image.height() / 5) * 4) // sprawdzenie pozycji 3
      {
        devR = tmpColor.red();
        devG = tmpColor.green();
        devB = tmpColor.blue();
      } else if (i == image.width() / 5 && j == (image.height() / 5) * 4) {

        if (rgbSearchList.value(6) > devR) {
          tmpDev += rgbSearchList.value(6) - devR;
        } else
          tmpDev += devR - rgbSearchList.value(6);

        if (rgbSearchList.value(7) > devG) {
          tmpDev += rgbSearchList.value(7) - devG;
        } else
          tmpDev += devG - rgbSearchList.value(7);

        if (rgbSearchList.value(8) > devB) {
          tmpDev += rgbSearchList.value(8) - devB;
        } else
          tmpDev += devB - rgbSearchList.value(8);

        devR = 0;
        devG = 0;
        devB = 0;

        deviationList.push_back(tmpDev);
        tmpDev = 0;
      }

      if ((i > (image.width() / 5) * 2 && i < (image.width() / 5) * 3) &&
          j < (image.height() / 5) * 4) // sprawdzenie pozycji 4
      {
        devR = tmpColor.red();
        devG = tmpColor.green();
        devB = tmpColor.blue();
      } else if (i == ((image.width() / 5) * 3) + 1 &&
                 j == image.height() - 1) {
        if (rgbSearchList.value(9) > devR) {
          tmpDev += rgbSearchList.value(9) - devR;
        } else
          tmpDev += devR - rgbSearchList.value(9);

        if (rgbSearchList.value(10) > devG) {
          tmpDev += rgbSearchList.value(10) - devG;
        } else
          tmpDev += devG - rgbSearchList.value(10);

        if (rgbSearchList.value(11) > devB) {
          tmpDev += rgbSearchList.value(11) - devB;
        } else
          tmpDev += devB - rgbSearchList.value(11);

        devR = 0;
        devG = 0;
        devB = 0;

        deviationList.push_back(tmpDev);
        tmpDev = 0;
      }

      if ((i > (image.width() / 5) * 4 && i != image.width() - 1) &&
          (j > (image.height() / 5) * 4 &&
           j != image.height() - 1)) // sprawdzenie pozycji 5
      {
        devR = tmpColor.red();
        devG = tmpColor.green();
        devB = tmpColor.blue();

      } else if (i == image.width() - 1 && j == image.height() - 1) {
        if (rgbSearchList.value(12) > devR) {
          tmpDev += rgbSearchList.value(12) - devR;
        } else
          tmpDev += devR - rgbSearchList.value(12);

        if (rgbSearchList.value(13) > devG) {
          tmpDev += rgbSearchList.value(13) - devG;
        } else
          tmpDev += devG - rgbSearchList.value(13);

        if (rgbSearchList.value(14) > devB) {
          tmpDev += rgbSearchList.value(14) - devB;
        } else
          tmpDev += devB - rgbSearchList.value(14);

        devR = 0;
        devG = 0;
        devB = 0;

        deviationList.push_back(tmpDev);
        tmpDev = 0;
      }
    }
  }

  int lowestDev = deviationList.value(2);
  int suggestedPos = 2;
  for (int i = 0; i < deviationList.size(); i++)
    if (deviationList.value(i) < lowestDev) {
      lowestDev = deviationList.value(i);
      suggestedPos = i;
    }

  if (suggestedPos == 0) { // pozycja 1
    if (image.width() > image.height()) {
      watermarkCoordinates[0] = image.width() / 10;
      watermarkCoordinates[1] = image.width() / 10;
    } else {
      watermarkCoordinates[0] = image.height() / 10;
      watermarkCoordinates[1] = image.height() / 10;
    }

  } else if (suggestedPos == 1) { // pozycja 2
    if (image.width() > image.height()) {
      watermarkCoordinates[0] = (image.width() / 10) * 9;
      watermarkCoordinates[1] = (image.width() / 10) * 9;
    } else {
      watermarkCoordinates[0] = image.height() / 10;
      watermarkCoordinates[1] = image.height() / 10;
    }
  } else if (suggestedPos == 2) { // pozycja 3
    if (image.width() > image.height()) {
      watermarkCoordinates[0] = image.width() / 10;
      watermarkCoordinates[1] = image.height() - (image.width() / 10);
    } else {
      watermarkCoordinates[0] = image.height() / 10;
      watermarkCoordinates[1] = (image.height() / 10) * 9;
    }
  } else if (suggestedPos == 3) { // pozycja 4
    watermarkCoordinates[0] = (image.width() / 10) * 5;
    watermarkCoordinates[1] = (image.height() / 10) * 9;
  } else { // pozycja 5
    if (image.width() > image.height()) {
      watermarkCoordinates[0] = (image.width() / 10) * 9;
      watermarkCoordinates[1] = (image.width() / 10) * 9;
    } else {
      watermarkCoordinates[0] = (image.height() / 10) * 9;
      watermarkCoordinates[1] = (image.height() / 10) * 9;
    }
  }

  watermarkCoordinatesList.push_back(watermarkCoordinates[0]);
  watermarkCoordinatesList.push_back(watermarkCoordinates[1]);
}

void MainWindow::markImage(int image) {
  int tmpNum = 0;
  int x = 0;
  int y = 0;
  int tmp = 64;

  if (image > 0)
    for (int i = 0; i < image; i++)
      tmpNum += 2;

  QImage tmpLogo;

  if (imageList[image].width() > imageList[image].height())
    tmpLogo = logo.scaledToWidth(imageList[image].height() / 5);
  else
    tmpLogo = logo.scaledToWidth(imageList[image].width() / 5);

  for (int i = watermarkCoordinatesList[tmpNum] - tmpLogo.width() / 2;
       i < watermarkCoordinatesList[tmpNum] + imageList[image].width() / 2 / 5;
       i++) {
    y = 0;
    for (int j = watermarkCoordinatesList[tmpNum + 1] - tmpLogo.height() / 2;
         j < watermarkCoordinatesList[tmpNum + 1] +
                 imageList[image].height() / 2 / 5;
         j++) {

      int tmpR = 0;
      int tmpG = 0;
      int tmpB = 0;

      if (x < tmpLogo.width() && y < tmpLogo.height())
        if (tmpLogo.pixelColor(x, y) != Qt::white) {

          tmpR = imageList[image].pixelColor(i, j).red() + tmp;
          tmpG = imageList[image].pixelColor(i, j).green() + tmp;
          tmpB = imageList[image].pixelColor(i, j).blue() + tmp;

          if (tmpR > 255)
            tmpR = 255;
          if (tmpG > 255)
            tmpG = 255;
          if (tmpB > 255)
            tmpB = 255;

          QColor markedColor(tmpR, tmpG, tmpB);
          imageList[image].setPixelColor(i, j, markedColor);
        }
      y++;
    }
    x++;
  }
}

void MainWindow::on_btnSave_clicked() {

  if (imageList.empty() == false) {
    QString filePath = QFileDialog::getExistingDirectory(this, "Get Any File");

    for (int i = 0; i < imageList.size(); i++) {
      imageList[i].save(filePath + "//" + nameList[i] + "_marked.jpg", nullptr,
                        -1);
    }

    clearLbl();
    imageList.clear();
    nameList.clear();
    infoList.clear();
    rgbSearchList.clear();
    deviationList.clear();
    watermarkCoordinatesList.clear();
  }
}
