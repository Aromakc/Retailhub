/*
Name: QtRpt
Version: 2.1.0
Web-site: http://www.qtrpt.tk
Programmer: Aleksey Osipov
E-mail: aliks-os@ukr.net
Web-site: http://www.aliks-os.tk

Copyright 2012-2020 Aleksey Osipov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef EXAMPLEDLG13_H
#define EXAMPLEDLG13_H

#include <QDialog>
#include "qtrpt.h"

namespace Ui {
    class ExampleDlg13;
}

class ExampleDlg13 : public QDialog
{
    Q_OBJECT

public:
    explicit ExampleDlg13(QWidget *parent = 0);
    ~ExampleDlg13();

private:
    Ui::ExampleDlg13 *ui;

private slots:
    void print();
    void setField(RptFieldObject &);
    void setDSInfo(DataSetInfo &dsInfo);
};

#endif // EXAMPLEDLG13_H