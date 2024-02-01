#include <QApplication>
#include <QColor>
#include <QEvent>
#include <QFileDialog>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTextEdit>
#include <QTime>
#include <QTimer>
#include <QWidget>

class Safebook : public QWidget {
public:
  Safebook(QWidget *parent = nullptr) : QWidget(parent) {
    setFixedSize(1200, 700);
    setStyleSheet("background-color:rgb(222, 222, 222)");

    QFrame *shadowBox = new QFrame(this);
    shadowBox->setGeometry(400, 165, 400, 370);
    shadowBox->hide();

    QGraphicsDropShadowEffect *dropShadow =
        new QGraphicsDropShadowEffect(shadowBox);
    dropShadow->setBlurRadius(25);
    dropShadow->setColor(QColor(0, 0, 0, 160));
    dropShadow->setOffset(0, 5);
    shadowBox->setGraphicsEffect(dropShadow);

    shadowBox->setStyleSheet("border-width: 0px; border-radius: 10px;");

    // LoginFrame
    loginFrame = new QFrame(this);
    loginFrame->setObjectName("loginFrame");
    loginFrame->setGeometry(400, 165, 400, 370);
    loginFrame->hide();

    loginFrame->setStyleSheet("background-color: rgb(255,255,255); "
                              "border-width: 0px; border-radius: 10px;");

    QFrame *usernameFrame = new QFrame(loginFrame);
    usernameFrame->setGeometry(15, 20, 370, 50);
    usernameFrame->setStyleSheet(
        "border: 2px solid rgba(222, 222, 222, 255); border-width: 2px;");

    QLineEdit *usernameInput = new QLineEdit(usernameFrame);
    usernameInput->setGeometry(20, 10, 340, 30);
    usernameInput->setFont(QFont("Verdana", 12));
    usernameInput->setStyleSheet("color: rgb(0, 0, 0); border-width: 0px;");
    usernameInput->setPlaceholderText("E-mail");

    QFrame *passwordFrame = new QFrame(loginFrame);
    passwordFrame->setGeometry(15, 80, 370, 50);
    passwordFrame->setStyleSheet(
        "border: 2px solid rgba(222, 222, 222, 255); border-width: 2px;");

    QLineEdit *passwordInput = new QLineEdit(passwordFrame);
    passwordInput->setGeometry(20, 10, 340, 30);
    passwordInput->setFont(QFont("Verdana", 12));
    passwordInput->setStyleSheet("color: rgb(0, 0, 0); border-width: 0px;");
    passwordInput->setPlaceholderText("Password");

    QPushButton *LoginsourceBtn = new QPushButton(loginFrame);
    LoginsourceBtn->setGeometry(15, 150, 370, 50);
    LoginsourceBtn->setFont(QFont("Verdana", 14, QFont::Bold));
    LoginsourceBtn->setStyleSheet("background-color: rgb(24, 119, 242); color: "
                                  "rgb(255, 255, 255); border-radius: 8px;");
    LoginsourceBtn->setText("Log in");

    QFrame *splitLine = new QFrame(loginFrame);
    splitLine->setGeometry(10, 240, 380, 1);
    splitLine->setStyleSheet(
        "background-color: rgba(222, 222, 222,255); border-width: 0px;");

    createNewAccountsourceBtn = new QPushButton(loginFrame);
    createNewAccountsourceBtn->setGeometry(75, 275, 250, 60);
    createNewAccountsourceBtn->setFont(QFont("Verdana", 12, QFont::Bold));
    createNewAccountsourceBtn->setStyleSheet(
        "background-color: rgb(66, 183, 42); border-radius: 8px;");
    createNewAccountsourceBtn->setText("Create new account");

    connect(createNewAccountsourceBtn, &QPushButton::clicked, loginFrame,
            [=]() {
              fadeOutFrame(loginFrame, createAccountFrame, logInOpacityEffect,
                           createAccountOpacityEffect);
            });

    logInOpacityEffect = new QGraphicsOpacityEffect(loginFrame);
    loginFrame->setGraphicsEffect(logInOpacityEffect);

    // CreateAccountFrame
    createAccountFrame = new QFrame(this);
    createAccountFrame->setObjectName("createAccountFrame");
    createAccountFrame->setGeometry(400, 165, 400, 370);

    createAccountFrame->setStyleSheet(
        "background-color: rgba(255, 255, 255,255); border-radius: 10px;");
    createAccountFrame->hide();

    QFrame *usernameFrame2 = new QFrame(createAccountFrame);
    usernameFrame2->setGeometry(15, 20, 370, 50);
    usernameFrame2->setStyleSheet(
        "border: 2px solid rgba(222, 222, 222, 255); border-width: 2px;");
    usernameFrame2->setFrameShape(QFrame::StyledPanel);
    usernameFrame2->setFrameShadow(QFrame::Raised);

    QLineEdit *usernameInput2 = new QLineEdit(usernameFrame2);
    usernameInput2->setGeometry(20, 10, 340, 30);
    usernameInput2->setFont(QFont("Verdana", 12));
    usernameInput2->setStyleSheet("color: rgb(0, 0, 0); border-width: 0px;");
    usernameInput2->setPlaceholderText("E-mail");

    QFrame *passwordFrame2 = new QFrame(createAccountFrame);
    passwordFrame2->setGeometry(15, 80, 370, 50);
    passwordFrame2->setStyleSheet(
        "border: 2px solid rgba(222, 222, 222, 255); border-width: 2px;");
    passwordFrame2->setFrameShape(QFrame::StyledPanel);
    passwordFrame2->setFrameShadow(QFrame::Raised);

    QLineEdit *passwordInput2 = new QLineEdit(passwordFrame2);
    passwordInput2->setGeometry(20, 10, 340, 30);
    passwordInput2->setFont(QFont("Verdana", 12));
    passwordInput2->setStyleSheet("color: rgb(0, 0, 0); border-width: 0px;");
    passwordInput2->setPlaceholderText("Password");

    QPushButton *registratesourceBtn = new QPushButton(createAccountFrame);
    registratesourceBtn->setGeometry(15, 150, 370, 50);
    registratesourceBtn->setFont(QFont("Verdana", 14, QFont::Bold));
    registratesourceBtn->setStyleSheet(
        "background-color: rgb(66, 183, 42); color: "
        "rgb(255, 255, 255); border-radius: 8px;");
    registratesourceBtn->setText("Registrate");

    QFrame *splitLine2 = new QFrame(createAccountFrame);
    splitLine2->setGeometry(10, 240, 380, 1);
    splitLine2->setStyleSheet(
        "background-color: rgb(222, 222, 222); border-width: 0px;");

    goBacksourceBtn = new QPushButton(createAccountFrame);
    goBacksourceBtn->setGeometry(75, 275, 250, 60);
    goBacksourceBtn->setFont(QFont("Verdana", 12, QFont::Bold));
    goBacksourceBtn->setStyleSheet(
        "background-color: rgb(24, 119, 242); border-radius: 8px;");
    goBacksourceBtn->setText("Go back");

    connect(goBacksourceBtn, &QPushButton::clicked, this, [=]() {
      fadeOutFrame(createAccountFrame, loginFrame, createAccountOpacityEffect,
                   logInOpacityEffect);
    });

    createAccountOpacityEffect = new QGraphicsOpacityEffect(createAccountFrame);
    createAccountFrame->setGraphicsEffect(createAccountOpacityEffect);

    // LoggedIn Frame this is the one not working with bg-color
    loggedInBgFrame = new QFrame(this);
    loggedInBgFrame->setGeometry(0, 0, 1200, 700);
    loggedInBgFrame->setStyleSheet(
        "background-image: url(../resources/bg.jpg)");
    loggedInBgFrame->show();

    loggedInFrame = new QFrame(this);
    loggedInFrame->setGeometry(0, 0, 1200, 700);
    loggedInFrame->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    sourceBtn = new QPushButton(loggedInFrame);
    sourceBtn->setGeometry(186, 188, 60, 28);
    sourceBtn->setObjectName("sourceBtn");
    sourceBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    sourceBtn->installEventFilter(this);

    sourcePath = new QLabel("C:/Users/krant/Desktop/abc.txt ✓", loggedInFrame);
    sourcePath->setGeometry(253, 190, 327, 30);
    sourcePath->setFont(QFont("Verdana", 10, QFont::Bold));
    sourcePath->setStyleSheet("color: rgba(143,140,197,255);");

    connect(sourceBtn, &QPushButton::clicked,
            [=]() { openFileDialog(sourceBtn, sourcePath); });

    targetBtn = new QPushButton(loggedInFrame);
    targetBtn->setGeometry(186, 240, 60, 28);
    targetBtn->setObjectName("targetBtn");
    targetBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    targetBtn->installEventFilter(this);

    targetPath = new QLabel("C:/Users/krant/Desktop/abc.txt", loggedInFrame);
    targetPath->setGeometry(253, 242, 327, 30);
    targetPath->setFont(QFont("Verdana", 10, QFont::Bold));
    targetPath->setStyleSheet("color: rgba(143,140,197,255);");

    connect(targetBtn, &QPushButton::clicked,
            [=]() { openFileDialog(targetBtn, targetPath); });

    md5Btn = new QPushButton(loggedInFrame);
    md5Btn->setGeometry(554, 330, 25, 20);
    md5Btn->setObjectName("md5Btn");
    md5Btn->setStyleSheet("background-color: rgba(27,21,160,0); border: none; "
                          "border-radius: 5px;");

    md5Btn->installEventFilter(this);

    connect(md5Btn, &QPushButton::clicked, [=]() { checksCheckBoxes(md5Btn); });

    sha256Btn = new QPushButton(loggedInFrame);
    sha256Btn->setGeometry(554, 367, 25, 20);
    sha256Btn->setObjectName("sha256Btn");
    sha256Btn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    sha256Btn->installEventFilter(this);

    connect(sha256Btn, &QPushButton::clicked,
            [=]() { checksCheckBoxes(sha256Btn); });

    bruteforceBtn = new QPushButton(loggedInFrame);
    bruteforceBtn->setGeometry(554, 403, 25, 20);
    bruteforceBtn->setObjectName("bruteforceBtn");
    bruteforceBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    bruteforceBtn->installEventFilter(this);

    connect(bruteforceBtn, &QPushButton::clicked,
            [=]() { checksCheckBoxes(bruteforceBtn); });

    startBtn = new QPushButton(loggedInFrame);
    startBtn->setGeometry(70, 528, 100, 50);
    startBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    startBtn->installEventFilter(this);

    connect(startBtn, &QPushButton::clicked, this, &Safebook::startTimer);

    stopBtn = new QPushButton(loggedInFrame);
    stopBtn->setGeometry(186, 528, 100, 50);
    stopBtn->setStyleSheet("background-color: rgba(27,21,160,0); border: none; "
                           "border-radius: 5px;");

    stopBtn->installEventFilter(this);

    connect(stopBtn, &QPushButton::clicked, this, &Safebook::startTimer);

    crackedPasswords = new QTextEdit(loggedInFrame);
    crackedPasswords->setGeometry(637, 170, 473, 400);
    crackedPasswords->setFont(QFont("Verdana", 10, QFont::Bold));
    crackedPasswords->setPlainText("#: f73g8h489h3d6 \nP: Grisen!254");
    crackedPasswords->setReadOnly(true);
    crackedPasswords->setStyleSheet(
        "color: rgba(143,140,197,255); border: none;");
    crackedPasswords->show();

    timerDisplay =
        new QLabel("00:00:00", loggedInFrame); // diffrent thread maybe?!
    timerDisplay->setGeometry(376, 535, 150, 50);
    timerDisplay->setFont(QFont("Verdana", 18, QFont::Bold));
    timerDisplay->setStyleSheet("color: rgba(143,140,197,255); border: none;");

    timer = new QTimer(loggedInFrame);

    connect(timer, &QTimer::timeout, this, &Safebook::updateTimer);
  }

private:
  QFrame *loginFrame;
  QFrame *createAccountFrame;
  QFrame *loggedInBgFrame;
  QFrame *loggedInFrame;
  QPushButton *createNewAccountsourceBtn;
  QPushButton *goBacksourceBtn;
  QPushButton *sourceBtn;
  QPushButton *targetBtn;
  QPushButton *startBtn;
  QPushButton *stopBtn;
  QPushButton *md5Btn;
  QPushButton *sha256Btn;
  QPushButton *bruteforceBtn;
  QLabel *sourcePath;
  QLabel *targetPath;
  QLabel *timerDisplay;
  QTimer *timer;
  QTime currentTime;

  QTextEdit *crackedPasswords;
  QGraphicsOpacityEffect *logInOpacityEffect;
  QGraphicsOpacityEffect *createAccountOpacityEffect;

  bool md5Checked = false;
  bool sha256Checked = false;
  bool bruteforceChecked = false;

protected:
  bool eventFilter(QObject *obj, QEvent *event) override {
    if (event->type() == QEvent::Enter || event->type() == QEvent::Leave) {
      // Source Button
      if (obj == sourceBtn) {
        sourceBtn->setStyleSheet(
            event->type() == QEvent::Enter
                ? "background-color: rgba(143,140,197,100); border: none; "
                  "border-radius: 5px;"
                : "background-color: rgba(27,21,160,0);; border-radius: "
                  "5px;");
      }
      // Target Button
      else if (obj == targetBtn) {
        targetBtn->setStyleSheet(
            event->type() == QEvent::Enter
                ? "background-color: rgba(143,140,197,100);; border-radius: "
                  "5px;"
                : "background-color: rgba(27,21,160,0);; border-radius: "
                  "5px;");
      }
      // Start Button
      else if (obj == startBtn) {
        startBtn->setStyleSheet(
            event->type() == QEvent::Enter
                ? "background-color: rgba(143,140,197,100); "
                  "border: none; border-radius: 5px;"
                : "background-color: rgba(27,21,160,0); "
                  "border: none; border-radius: 5px;");
      }
      // Stop Button
      else if (obj == stopBtn) {
        stopBtn->setStyleSheet(event->type() == QEvent::Enter
                                   ? "background-color: rgba(143,140,197,100); "
                                     "border: none; border-radius: 5px;"
                                   : "background-color: rgba(27,21,160,0); "
                                     "border: none; border-radius: 5px;");
      }
      // MD5 Button
      else if (obj == md5Btn && !md5Checked) {
        md5Btn->setStyleSheet(event->type() == QEvent::Enter
                                  ? "background-color: rgba(143,140,197,100); "
                                    "border: none; border-radius: 5px;"
                                  : "background-color: rgba(27,21,160,0); "
                                    "border: none; border-radius: 5px;");
      }
      // SHA-256 Button
      else if (obj == sha256Btn && !sha256Checked) {
        sha256Btn->setStyleSheet(
            event->type() == QEvent::Enter
                ? "background-color: rgba(143,140,197,100); "
                  "border: none; border-radius: 5px;"
                : "background-color: rgba(27,21,160,0); "
                  "border: none; border-radius: 5px;");
      }
      // BruteForce Button
      else if (obj == bruteforceBtn && !bruteforceChecked) {
        bruteforceBtn->setStyleSheet(
            event->type() == QEvent::Enter
                ? "background-color: rgba(143,140,197,100); "
                  "border: none; border-radius: 5px;"
                : "background-color: rgba(27,21,160,0); "
                  "border: none; border-radius: 5px;");
      }
    }

    // Pass the event to the base class
    return QWidget::eventFilter(obj, event);
  }

  void openFileDialog(QPushButton *button, QLabel *labelToUpdate) {
    if (button->objectName() == "sourceBtn") {
      QString filePath = QFileDialog::getOpenFileName(
          this, "Choose Source Path", QDir::homePath(), "Text Files (*.txt)");

      if (!filePath.isEmpty() && labelToUpdate) {

        labelToUpdate->setText(filePath);
      }
    } else if (button->objectName() == "targetBtn") {

      QString filePath = QFileDialog::getOpenFileName(
          this, "Choose Target Path", QDir::homePath(), "Text Files (*.txt)");

      if (!filePath.isEmpty() && labelToUpdate) {

        labelToUpdate->setText(filePath);
      }
    }
  }

private slots:

  void fadeOutFrame(QFrame *frameToFadeOut, QFrame *frameToFadeIn,
                    QGraphicsOpacityEffect *fadeOutOpacityEffect,
                    QGraphicsOpacityEffect *fadeInOpacityEffect) {
    QPropertyAnimation *fadeOutAnimation =
        new QPropertyAnimation(fadeOutOpacityEffect, "opacity");
    fadeOutAnimation->setDuration(300);
    fadeOutAnimation->setStartValue(1.0);
    fadeOutAnimation->setEndValue(0.0);

    connect(fadeOutAnimation, &QPropertyAnimation::finished, this, [=]() {
      fadeInFrame(frameToFadeIn, frameToFadeOut, fadeInOpacityEffect);
    });

    fadeOutAnimation->start();
  }

  void fadeInFrame(QFrame *frameToFadeIn, QFrame *frameToFadeOut,
                   QGraphicsOpacityEffect *fadeInOpacityEffect) {
    frameToFadeIn->show();

    QPropertyAnimation *fadeInAnimation =
        new QPropertyAnimation(fadeInOpacityEffect, "opacity");
    fadeInAnimation->setDuration(300);
    fadeInAnimation->setStartValue(0.0);
    fadeInAnimation->setEndValue(1.0);

    connect(fadeInAnimation, &QPropertyAnimation::finished, frameToFadeOut,
            [=]() { frameToFadeOut->hide(); });

    fadeInAnimation->start();
  }

  void checksCheckBoxes(QPushButton *button) {
    if (button->objectName() == "md5Btn") {

      if (!md5Checked) {
        md5Btn->setStyleSheet(
            "background-color: rgba(143,140,197,100); border: none; "
            "border-radius: 5px;");
        sha256Btn->setStyleSheet(
            "background-color: rgba(143,140,197,0); border: none; "
            "border-radius: 5px;");
        bruteforceBtn->setStyleSheet(
            "background-color: rgba(143,140,197,0); border: none; "
            "border-radius: 5px;");

        md5Checked = true;
        sha256Checked = false;
        bruteforceChecked = false;
      } else {
        md5Btn->setStyleSheet(
            "background-color: rgba(143,140,197,0); border: none; "
            "border-radius: 5px;");
        md5Checked = false;
      }

    } else if (button->objectName() == "sha256Btn") {

      if (!sha256Checked) {
        sha256Btn->setStyleSheet(
            "background-color: rgba(143,140,197,100); border: none; "
            "border-radius: 5px;");
        md5Btn->setStyleSheet(
            "background-color: rgba(143,140,197,0); border: none; "
            "border-radius: 5px;");
        bruteforceBtn->setStyleSheet(
            "background-color: rgba(143,140,197,0); border: none; "
            "border-radius: 5px;");

        sha256Checked = true;
        bruteforceChecked = false;
        md5Checked = false;
      } else {
        sha256Btn->setStyleSheet(
            "background-color: rgba(143,140,197,0); border: none; "
            "border-radius: 5px;");
        sha256Checked = false;
      }

    } else if (button->objectName() == "bruteforceBtn") {

      if (!bruteforceChecked) {
        bruteforceBtn->setStyleSheet(
            "background-color: rgba(143,140,197,100); border: none; "
            "border-radius: 5px;");
        sha256Btn->setStyleSheet(
            "background-color: rgba(143,140,197,0); border: none; "
            "border-radius: 5px;");
        md5Btn->setStyleSheet(
            "background-color: rgba(143,140,197,0); border: none; "
            "border-radius: 5px;");

        bruteforceChecked = true;
        sha256Checked = false;
        md5Checked = false;
      } else {
        bruteforceBtn->setStyleSheet(
            "background-color: rgba(143,140,197,0); border: none; "
            "border-radius: 5px;");
        bruteforceChecked = false;
      }
    }
  }

  void startTimer() {
    // Start the timer
    timer->start(1000); // Update every 1000 milliseconds (1 second)

    // Enable/disable buttons accordingly
    startBtn->setEnabled(false);
    stopBtn->setEnabled(true);
  }

  void stopTimer() {
    // Stop the timer
    timer->stop();

    // Enable/disable buttons accordingly
    startBtn->setEnabled(true);
    stopBtn->setEnabled(false);
  }

  void updateTimer() {
    qDebug() << "Entering calculateFormattedTime function";
    // Increment the time by one second
    currentTime = currentTime.addSecs(1);
    // QMessageBox::information(nullptr, "Information",
    //                        "Time:currentTime");
    // Format the time as "hh:mm:ss"
    QString formattedTime = currentTime.toString("hh:mm:ss");

    // Update the QLabel with the formatted time
    timerDisplay->setText(formattedTime);
  }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Safebook safebook;
  safebook.show();

  return app.exec();
}
