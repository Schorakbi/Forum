#ifndef POSTANDREPLIESDIALOG_H
#define POSTANDREPLIESDIALOG_H

#include <QDialog>

namespace Ui {
class postandrepliesDialog;
}

class postandrepliesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit postandrepliesDialog(QWidget *parent = nullptr);
    ~postandrepliesDialog();

private slots:


    void on_pushButton_clicked();

private:
    Ui::postandrepliesDialog *ui;
    int replyLabelIndex = -1;
};

#endif // POSTANDREPLIESDIALOG_H
