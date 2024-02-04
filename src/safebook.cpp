#include <QApplication>
#include <QColor>
#include <QEvent>
#include <QFileDialog>
#include <QFont>
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
#include <string>
#include <userManager.h>

class Safebook : public QWidget {
public:
  Safebook(QWidget *parent = nullptr) : QWidget(parent) {
    setFixedSize(1200, 700);
    setStyleSheet("background-color:rgb(222, 222, 222)");

    shadowBox = new QFrame(this);
    shadowBox->setGeometry(400, 165, 400, 370);
    shadowBox->show();

    QGraphicsDropShadowEffect *dropShadow =
        new QGraphicsDropShadowEffect(shadowBox);
    dropShadow->setBlurRadius(25);
    dropShadow->setColor(QColor(0, 0, 0, 160));
    dropShadow->setOffset(0, 5);
    shadowBox->setGraphicsEffect(dropShadow);

    shadowBox->setStyleSheet("border-width: 0px; border-radius: 10px;");

    inputWarnings = new QLabel(this);
    inputWarnings->setGeometry(400, 135, 400, 30);
    inputWarnings->setFont(QFont("Verdana", 10, QFont::Bold));
    inputWarnings->setAlignment(Qt::AlignCenter);
    inputWarnings->setStyleSheet("color: rgba(169,0,6,200); "
                                 "border: none;");
    inputWarnings->hide();

    inputInfo = new QTextEdit(this);
    inputInfo->setGeometry(250, 165, 150, 150);
    inputInfo->setFont(QFont("Verdana", 8, QFont::Bold));
    inputInfo->setReadOnly(true);
    inputInfo->setStyleSheet(
        "background-color: rgba(255,255,255,0); border:none");
    inputInfo->hide();

    // LoginFrame
    loginFrame = new QFrame(this);
    loginFrame->setObjectName("loginFrame");
    loginFrame->setGeometry(400, 165, 400, 370);

    loginFrame->setStyleSheet("background-color: rgb(255,255,255); "
                              "border-width: 0px; border-radius: 10px;");

    QFrame *usernameFrame = new QFrame(loginFrame);
    usernameFrame->setGeometry(15, 20, 370, 50);
    usernameFrame->setStyleSheet(
        "border: 2px solid rgba(222, 222, 222, 255); border-width: 2px;");

    usernameInput = new QLineEdit(usernameFrame);
    usernameInput->setGeometry(20, 10, 340, 30);
    usernameInput->setFont(QFont("Verdana", 12));
    usernameInput->setStyleSheet("color: rgb(0, 0, 0); border-width: 0px;");
    usernameInput->setPlaceholderText("E-mail");

    QFrame *passwordFrame = new QFrame(loginFrame);
    passwordFrame->setGeometry(15, 80, 370, 50);
    passwordFrame->setStyleSheet(
        "border: 2px solid rgba(222, 222, 222, 255); border-width: 2px;");

    passwordInput = new QLineEdit(passwordFrame);
    passwordInput->setGeometry(20, 10, 340, 30);
    passwordInput->setFont(QFont("Verdana", 12));
    passwordInput->setStyleSheet("color: rgb(0, 0, 0); border-width: 0px;");
    passwordInput->setPlaceholderText("Password");

    loginBtn = new QPushButton(loginFrame);
    loginBtn->setGeometry(15, 150, 370, 50);
    loginBtn->setFont(QFont("Verdana", 14, QFont::Bold));
    loginBtn->setStyleSheet("background-color: rgb(24, 119, 242); color: "
                            "rgb(255, 255, 255); border-radius: 8px;");
    loginBtn->setText("Log in");

    connect(loginBtn, &QPushButton::clicked, loginFrame,
            [=]() { onLoginClick(); });

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
      fadeOutFrames(loginFrame, createAccountFrame, loginOpacityEffect,
                    createAccountOpacityEffect);
      inputInfo->hide();
      inputWarnings->hide();
    });

    loginOpacityEffect = new QGraphicsOpacityEffect(loginFrame);
    loginFrame->setGraphicsEffect(loginOpacityEffect);

    loginOpacityEffect->setOpacity(1.0);

    // CreateAccountFrame
    createAccountFrame = new QFrame(this);
    createAccountFrame->setObjectName("createAccountFrame");
    createAccountFrame->setGeometry(400, 165, 400, 370);
    createAccountFrame->hide();

    createAccountFrame->setStyleSheet(
        "background-color: rgba(255, 255, 255,255); border-radius: 10px;");

    QFrame *usernameFrame2 = new QFrame(createAccountFrame);
    usernameFrame2->setGeometry(15, 20, 370, 50);
    usernameFrame2->setStyleSheet(
        "border: 2px solid rgba(222, 222, 222, 255); border-width: 2px;");
    usernameFrame2->setFrameShape(QFrame::StyledPanel);
    usernameFrame2->setFrameShadow(QFrame::Raised);

    usernameInput2 = new QLineEdit(usernameFrame2);
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

    passwordInput2 = new QLineEdit(passwordFrame2);
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

    connect(registrateBtn, &QPushButton::clicked, createAccountFrame,
            [=]() { onRegistrationClick(); });

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
      fadeOutFrames(createAccountFrame, loginFrame, createAccountOpacityEffect,
                    loginOpacityEffect);
      inputInfo->hide();
      inputWarnings->hide();
      usernameInput->setText("");
      passwordInput->setText("");
    });

    createAccountOpacityEffect = new QGraphicsOpacityEffect(createAccountFrame);
    createAccountFrame->setGraphicsEffect(createAccountOpacityEffect);
    // admin@root.com
    createAccountOpacityEffect->setOpacity(0.0); // Ol!v3rtwist

    // Logged in Frame
    loggedInBgFrame = new QFrame(this);
    loggedInBgFrame->setGeometry(0, 0, 1200, 700);
    loggedInBgFrame->setObjectName("loggedInBgFrame");
    loggedInBgFrame->setStyleSheet(
        "background-image: url(../resources/bg.jpg)");
    loggedInBgFrame->hide();

    loggedInBgFrameOpacityEffect = new QGraphicsOpacityEffect(loggedInBgFrame);
    loggedInBgFrame->setGraphicsEffect(loggedInBgFrameOpacityEffect);

    loggedInBgFrameOpacityEffect->setOpacity(0.0);

    loggedInFrame = new QFrame(this);
    loggedInFrame->setGeometry(0, 0, 1200, 700);
    loggedInFrame->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    loggedInFrame->hide();

    loggedInFrameOpacityEffect = new QGraphicsOpacityEffect(loggedInFrame);
    loggedInFrame->setGraphicsEffect(loggedInFrameOpacityEffect);

    loggedInFrameOpacityEffect->setOpacity(0.0);

    sourceBtn = new QPushButton(loggedInFrame);
    sourceBtn->setGeometry(186, 188, 60, 28);
    sourceBtn->setFocusPolicy(Qt::NoFocus);
    sourceBtn->setObjectName("sourceBtn");
    sourceBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border-width:0px; "
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
    targetBtn->setFocusPolicy(Qt::NoFocus);
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
    md5Btn->setFocusPolicy(Qt::NoFocus);
    md5Btn->setObjectName("md5Btn");
    md5Btn->setStyleSheet("background-color: rgba(27,21,160,0); border: none; "
                          "border-radius: 5px;");

    md5Btn->installEventFilter(this);

    connect(md5Btn, &QPushButton::clicked, [=]() { checksCheckBoxes(md5Btn); });

    sha256Btn = new QPushButton(loggedInFrame);
    sha256Btn->setGeometry(554, 367, 25, 20);
    sha256Btn->setFocusPolicy(Qt::NoFocus);
    sha256Btn->setObjectName("sha256Btn");
    sha256Btn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    sha256Btn->installEventFilter(this);

    connect(sha256Btn, &QPushButton::clicked,
            [=]() { checksCheckBoxes(sha256Btn); });

    bruteforceBtn = new QPushButton(loggedInFrame);
    bruteforceBtn->setGeometry(554, 403, 25, 20);
    bruteforceBtn->setFocusPolicy(Qt::NoFocus);
    bruteforceBtn->setObjectName("bruteforceBtn");
    bruteforceBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    bruteforceBtn->installEventFilter(this);

    connect(bruteforceBtn, &QPushButton::clicked,
            [=]() { checksCheckBoxes(bruteforceBtn); });

    startBtn = new QPushButton(loggedInFrame);
    startBtn->setGeometry(70, 528, 100, 50);
    startBtn->setFocusPolicy(Qt::NoFocus);
    startBtn->setStyleSheet(
        "background-color: rgba(27,21,160,0); border: none; "
        "border-radius: 5px;");

    startBtn->installEventFilter(this);

    connect(startBtn, &QPushButton::clicked, this, &Safebook::startTimer);

    stopBtn = new QPushButton(loggedInFrame);
    stopBtn->setGeometry(186, 528, 100, 50);
    stopBtn->setFocusPolicy(Qt::NoFocus);
    stopBtn->setStyleSheet("background-color: rgba(27,21,160,0); border: none; "
                           "border-radius: 5px;");

    stopBtn->installEventFilter(this);

    connect(stopBtn, &QPushButton::clicked, this, &Safebook::stopTimer);

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
  }

private:
  QFrame *shadowBox;
  QFrame *loginFrame;
  QFrame *createAccountFrame;
  QFrame *loggedInBgFrame;
  QFrame *loggedInFrame;
  QPushButton *loginBtn;
  QPushButton *createNewAccountBtn;
  QPushButton *goBackBtn;
  QPushButton *sourceBtn;
  QPushButton *targetBtn;
  QPushButton *startBtn;
  QPushButton *stopBtn;
  QPushButton *md5Btn;
  QPushButton *sha256Btn;
  QPushButton *bruteforceBtn;
  QLineEdit *usernameInput;
  QLineEdit *passwordInput;
  QLineEdit *usernameInput2;
  QLineEdit *passwordInput2;
  QLabel *inputWarnings;
  QLabel *sourcePath;
  QLabel *targetPath;
  QLabel *timerDisplay;
  QTime currentTime;
  QTimer *timer;
  QTextEdit *crackedPasswords;
  QTextEdit *inputInfo;
  QGraphicsOpacityEffect *loginOpacityEffect;
  QGraphicsOpacityEffect *createAccountOpacityEffect;
  QGraphicsOpacityEffect *loggedInBgFrameOpacityEffect;
  QGraphicsOpacityEffect *loggedInFrameOpacityEffect;

  bool md5Checked = false;
  bool sha256Checked = false;
  bool bruteforceChecked = false;

  void startTimer() {
    // Initialize the current time to midnight
    currentTime = QTime(0, 0, 0);

    // Create a timer to update the display every second
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Safebook::updateTimer);
    timer->start(1000); // Update every 1000 milliseconds (1 second)

    startBtn->setEnabled(false);
    stopBtn->setEnabled(true);
  }

  void stopTimer() {
    timer->stop();

    startBtn->setEnabled(true);
    stopBtn->setEnabled(false);
  }

  UserManager userManager;

  void loginHandler(std::string username, std::string password) {

    int direction = userManager.loginUser(username, password);

    if (direction == 0) {

      fadeOutFrames(loginFrame, loggedInBgFrame, loginOpacityEffect,
                    loggedInBgFrameOpacityEffect);

    } else if (direction == 1) {

      inputWarnings->setText("Email Does Not Exist!");
      inputWarnings->show();

    } else if (direction == 2) {

      inputWarnings->setText("Wrong Password!");
      inputWarnings->show();
    }
  }

  void registrationHandler(std::string username, std::string password) {
    int direction = userManager.registerUser(username, password);

    if (direction == 0) {

      fadeOutFrames(createAccountFrame, loginFrame, createAccountOpacityEffect,
                    loginOpacityEffect);

    } else if (direction == 1) {

      inputWarnings->setText("Incorrect Email!");
      inputWarnings->show();

      inputInfo->setText("\n"
                         "Email must contain:\n"
                         "\n"
                         " @ and . \n"
                         "\n"
                         "Ex: abc@abc.abc");
      inputInfo->show();

    } else if (direction == 2) {

      inputWarnings->setText("Incorrect Password!");
      inputWarnings->show();

      inputInfo->setPlainText("\n"
                              "Password must atleast contain:\n"
                              "\n"
                              "• 8 charachters\n"
                              "• 1 capital letter\n"
                              "• 1 non-capital letter\n"
                              "• 1 digit\n"
                              "• 1 special character");
      inputInfo->show();

    } else if (direction == 3) {

      inputWarnings->setText("Incorrect Email and Password!");
      inputWarnings->show();

      inputInfo->setPlainText("\n"
                              "Password must atleast contain:\n"
                              "\n"
                              "• 8 charachters\n"
                              "• 1 capital letter\n"
                              "• 1 non-capital letter\n"
                              "• 1 digit\n"
                              "• 1 special character");
      inputInfo->show();
    }
  }

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

  void fadeOutFrames(QFrame *frameToFadeOut, QFrame *frameToFadeIn,
                     QGraphicsOpacityEffect *fadeOutOpacityEffect,
                     QGraphicsOpacityEffect *fadeInOpacityEffect) {

    QPropertyAnimation *fadeOutLoginAnimation =
        new QPropertyAnimation(fadeOutOpacityEffect, "opacity");
    fadeOutLoginAnimation->setDuration(300);
    fadeOutLoginAnimation->setStartValue(1.0);
    fadeOutLoginAnimation->setEndValue(0.0);

    if (frameToFadeIn->objectName() == "loggedInBgFrame") {

      connect(fadeOutLoginAnimation, &QPropertyAnimation::finished, this,
              [=]() { fadeInLoggedInFrame(); });
      fadeOutLoginAnimation->start();

    } else {

      connect(fadeOutLoginAnimation, &QPropertyAnimation::finished, this,
              [=]() {
                fadeInCreateAccountFrame(frameToFadeIn, frameToFadeOut,
                                         fadeInOpacityEffect);
              });
      fadeOutLoginAnimation->start();
    }
  }

  void fadeInCreateAccountFrame(QFrame *frameToFadeIn, QFrame *frameToFadeOut,
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

  void fadeInLoggedInFrame() {

    loggedInBgFrame->show();
    loggedInFrame->show();

    QPropertyAnimation *fadeInLoggedInBgAnimation =
        new QPropertyAnimation(loggedInBgFrameOpacityEffect, "opacity");
    fadeInLoggedInBgAnimation->setDuration(300);
    fadeInLoggedInBgAnimation->setStartValue(0.0);
    fadeInLoggedInBgAnimation->setEndValue(1.0);

    QPropertyAnimation *fadeInLoggedInAnimation =
        new QPropertyAnimation(loggedInFrameOpacityEffect, "opacity");
    fadeInLoggedInAnimation->setDuration(500);
    fadeInLoggedInAnimation->setStartValue(0.0);
    fadeInLoggedInAnimation->setEndValue(1.0);

    connect(fadeInLoggedInBgAnimation, &QPropertyAnimation::finished,
            loggedInBgFrame, [=]() {
              loginFrame->hide();
              fadeInLoggedInAnimation->start();
            });
    shadowBox->hide();
    fadeInLoggedInBgAnimation->start();
    // fadeInLoggedInAnimation->start();
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

  void updateTimer() {
    // Increment the time by one second
    currentTime = currentTime.addSecs(1);

    // Format the time as "hh:mm:ss"
    QString formattedTime = currentTime.toString("hh:mm:ss");

    // Update the QLabel with the formatted time
    timerDisplay->setText(formattedTime);
  }

  void onLoginClick() {

    inputInfo->hide();
    inputWarnings->hide();

    QString username = usernameInput->text();
    QString password = passwordInput->text();
    std::string convertedUsername = username.toStdString();
    std::string convertedPassword = password.toStdString();

    loginHandler(convertedUsername, convertedPassword);
  }

  void onRegistrationClick() {

    inputInfo->hide();
    inputWarnings->hide();

    QString username = usernameInput2->text();
    QString password = passwordInput2->text();
    std::string convertedUsername = username.toStdString();
    std::string convertedPassword = password.toStdString();

    registrationHandler(convertedUsername, convertedPassword);
  }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Safebook safebook;
  safebook.show();

  return app.exec();
}
