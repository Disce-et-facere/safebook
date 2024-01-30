#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QLineEdit>

class Safebook : public QWidget {
public:
    Safebook(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(1200, 700);
        setStyleSheet("background-color:rgb(222, 222, 222)");

        QFrame *shadowBox = new QFrame(this);
        shadowBox->setGeometry(400, 165, 400, 370);

        QGraphicsDropShadowEffect *dropShadow = new QGraphicsDropShadowEffect(shadowBox);
        dropShadow->setBlurRadius(25);
        dropShadow->setColor(QColor(0, 0, 0, 160));
        dropShadow->setOffset(0, 5);
        shadowBox->setGraphicsEffect(dropShadow);

        shadowBox->setStyleSheet("border-width: 0px; border-radius: 10px;");

        //LoginFrame
        loginFrame = new QFrame(this);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setGeometry(400, 165, 400, 370);

        loginFrame->setStyleSheet("background-color: rgb(255,255,255); border-width: 0px; border-radius: 10px;");

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

        QPushButton *LoginBtn = new QPushButton(loginFrame);
        LoginBtn->setGeometry(15, 150, 370, 50);
        LoginBtn->setFont(QFont("Verdana", 14, QFont::Bold));
        LoginBtn->setStyleSheet("background-color: rgb(24, 119, 242); color: "
                                "rgb(255, 255, 255); border-radius: 8px;");
        LoginBtn->setText("Log in");

        QFrame *splitLine = new QFrame(loginFrame);
        splitLine->setGeometry(10, 240, 380, 1);
        splitLine->setStyleSheet(
            "background-color: rgba(222, 222, 222,255); border-width: 0px;");

        createNewAccountBtn = new QPushButton(loginFrame);
        createNewAccountBtn->setGeometry(75, 275, 250, 60);
        createNewAccountBtn->setFont(QFont("Verdana", 12, QFont::Bold));
        createNewAccountBtn->setStyleSheet(
            "background-color: rgb(66, 183, 42); border-radius: 8px;");
        createNewAccountBtn->setText("Create new account");

        connect(createNewAccountBtn, &QPushButton::clicked, loginFrame, [=]() {
        fadeOutFrame(loginFrame, createAccountFrame, logInOpacityEffect,
                 createAccountOpacityEffect); });


        logInOpacityEffect = new QGraphicsOpacityEffect(loginFrame);
        loginFrame->setGraphicsEffect(logInOpacityEffect);

        //CreateAccountFrame
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

        QPushButton *registrateBtn = new QPushButton(createAccountFrame);
        registrateBtn->setGeometry(15, 150, 370, 50);
        registrateBtn->setFont(QFont("Verdana", 14, QFont::Bold));
        registrateBtn->setStyleSheet("background-color: rgb(66, 183, 42); color: "
                                    "rgb(255, 255, 255); border-radius: 8px;");
        registrateBtn->setText("Registrate");

        QFrame *splitLine2 = new QFrame(createAccountFrame);
        splitLine2->setGeometry(10, 240, 380, 1);
        splitLine2->setStyleSheet(
            "background-color: rgb(222, 222, 222); border-width: 0px;");

        goBackBtn = new QPushButton(createAccountFrame);
        goBackBtn->setGeometry(75, 275, 250, 60);
        goBackBtn->setFont(QFont("Verdana", 12, QFont::Bold));
        goBackBtn->setStyleSheet(
            "background-color: rgb(24, 119, 242); border-radius: 8px;");
        goBackBtn->setText("Go back");

        connect(goBackBtn, &QPushButton::clicked, this, [=]() {
        fadeOutFrame(createAccountFrame, loginFrame, createAccountOpacityEffect,
                    logInOpacityEffect);
        });

        createAccountOpacityEffect = new QGraphicsOpacityEffect(createAccountFrame);
        createAccountFrame->setGraphicsEffect(createAccountOpacityEffect);

    }
private:
  QFrame *loginFrame;
  QFrame *createAccountFrame;
  QPushButton *createNewAccountBtn;
  QPushButton *goBackBtn;
  QGraphicsOpacityEffect *logInOpacityEffect;
  QGraphicsOpacityEffect *createAccountOpacityEffect;

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
