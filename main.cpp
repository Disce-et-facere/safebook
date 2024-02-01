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
    loggedInBgFrame->setStyleSheet("background-image: url(../bg.jpg)");
    loggedInBgFrame->show();

    loggedInFrame = new QFrame(this);
    loggedInFrame->setGeometry(0, 0, 1200, 700);
    loggedInFrame->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    sourceBtn = new QPushButton(loggedInFrame);
    sourceBtn->setGeometry(186, 188, 60, 28);
    sourceBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    sourceBtn->installEventFilter(this);

    QLabel *sourcePath =
        new QLabel("C:/Users/krant/Desktop/abc.txt", loggedInFrame);
    sourcePath->setGeometry(253, 188, 327, 30);
    sourcePath->setFont(QFont("Verdana", 12));
    sourcePath->setStyleSheet("color: rgba(27,21,237,150); box-shadow: 0 0 "
                              "10px rgba(255, 255, 255, 0.8);");

    connect(sourceBtn, &QPushButton::clicked,
            [=]() { openFileDialog(sourcePath); });

    targetBtn = new QPushButton(loggedInFrame);
    targetBtn->setGeometry(186, 240, 60, 28);
    targetBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    targetBtn->installEventFilter(this);

    startBtn = new QPushButton(loggedInFrame);
    startBtn->setGeometry(70, 528, 100, 50);
    startBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    startBtn->installEventFilter(this);
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
  QLabel *sourcePath;
  QGraphicsOpacityEffect *logInOpacityEffect;
  QGraphicsOpacityEffect *createAccountOpacityEffect;

protected:
  bool eventFilter(QObject *obj, QEvent *event) override {
    if (event->type() == QEvent::Enter || event->type() == QEvent::Leave) {
      // Check for the first button
      if (obj == sourceBtn) {
        sourceBtn->setStyleSheet(
            event->type() == QEvent::Enter
                ? "background-color: rgba(27,21,160,100); border: none; "
                  "border-radius: 5px;"
                : "background-color: rgba(27,21,160,0);; border-radius: 5px;");
      }
      // Check for the second button
      else if (obj == targetBtn) {
        targetBtn->setStyleSheet(
            event->type() == QEvent::Enter
                ? "background-color: rgba(27,21,160,100);; border-radius: 5px;"
                : "background-color: rgba(27,21,160,0);; border-radius: 5px;");
      }
      // Check for the third button
      else if (obj == startBtn) {
        startBtn->setStyleSheet(event->type() == QEvent::Enter
                                    ? "background-color: rgba(27,21,160,100); "
                                      "border: none; border-radius: 5px;"
                                    : "background-color: rgba(27,21,160,0); "
                                      "border: none; border-radius: 5px;");
      }
    }

    // Pass the event to the base class
    return QWidget::eventFilter(obj, event);
  }

  void openFileDialog(QLabel *labelToUpdate) {

    QString filePath = QFileDialog::getOpenFileName(
        this, "Open TXT File", QDir::homePath(), "Text Files (*.txt)");
    // QMessageBox::information(nullptr, "Information", "Before.");
    if (!filePath.isEmpty() && labelToUpdate) {

      labelToUpdate->setText(filePath);
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
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Safebook safebook;
  safebook.show();

  return app.exec();
}
