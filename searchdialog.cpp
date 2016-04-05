#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Расширенный поиск"));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Поиск"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отмена"));
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_buttonBox_accepted()
{
    // Флаги, отмечающие, какие таблицы используются
    bool useTeach = false;       // Преподаватели
    bool useStud = false;       // Учащиеся
    bool useAss = false;        // Объединения              Да-да, это любимое сокращение Dive (dive155)
    bool useGroup = false;      // Группы

    QString *columns = new QString();
    QString *from = new QString();
    QString *where = new QString();
    QString *query = new QString();

    QStringList *fromStud = new QStringList();
    QStringList *fromTeach = new QStringList();
    QStringList *fromAss = new QStringList();
    QStringList *fromGroup = new QStringList();

    QStringList *whereStud = new QStringList();
    QStringList *whereTeach = new QStringList();
    QStringList *whereAss = new QStringList();
    QStringList *whereGroup = new QStringList();

    // ---------------------------------------------------------------
    // ------------------------ Преподаватель ------------------------
    // ---------------------------------------------------------------

    if (ui->teachName_ch->isChecked())      // Если чекнут чекбокс
    {
        fromTeach->append("Имя");           // Заносим в стринглист имя поля, которому соотвествует этот чекбокс
        useTeach = true;                     // И поднимаем флаг "Используем эту таблицу!"
    }

    if (ui->teachSurname_ch->isChecked())
    {
        fromTeach->append("Фамилия");           // Человек, решивший передалать эту прогу и переименовать поля в базе будет страдать.
        useTeach = true;                         // Очень сильно страдать.
    }

    if (ui->teachPatrname_ch->isChecked())
    {
        fromTeach->append("Отчество");
        useTeach = true;
    }

    if (ui->teachPass_ch->isChecked())
    {
        fromTeach->append("Паспорт");
        useTeach = true;
    }

    if (ui->teachOtd_ch->isChecked())
    {
        fromTeach->append("Отдел");
        useTeach = true;
    }

    // ---------------------------------------------------------------

    if (ui->teachName->isModified())        // Если textEdit был изменён
    {
        QString str = ui->teachName->text().simplified().replace(QRegularExpression("-{2,}"), "-");           // Берём из него инфу, отрезав вс лишнее
        if (!str.isEmpty())         // Если после отрезания от инфы что-нибудь осталось
        {
            whereTeach->append("Имя");      // То заносим в стринглист имя поля и его значение
            whereTeach->append(str);
            useTeach = true;
        }
    }

    if (ui->teachSurname->isModified())
    {
        QString str = ui->teachSurname->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
        whereTeach->append("Фамилия");
        whereTeach->append(str);
        useTeach = true;
        }
    }

    if (ui->teachPatrname->isModified())
    {
        QString str = ui->teachPatrname->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
        whereTeach->append("Отчество");
        whereTeach->append(str);
        useTeach = true;
        }
    }

    if (ui->teachPass->isModified())
    {
        QString str = ui->teachPass->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
        whereTeach->append("Паспорт");
        whereTeach->append(str);
        useTeach = true;
        }
    }

    if (ui->teachOtd->isModified())
    {
        QString str = ui->teachOtd->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
        whereTeach->append("Отдел");
        whereTeach->append(str);
        useTeach = true;
        }
    }

    // ---------------------------------------------------------------
    // -------------------------- Группа -----------------------------
    // ---------------------------------------------------------------

    if (ui->grNum_ch->isChecked())
    {
        fromGroup->append("Номер");
        useGroup = true;
    }

    if (ui->grYear_ch->isChecked())
    {
        fromGroup->append("Год обучения");
        useGroup = true;
    }

    // ---------------------------------------------------------------

    if (ui->grNum->isModified())
    {
        QString str = ui->grNum->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereGroup->append("Номер");
            whereGroup->append(str);
            useTeach = true;
        }
    }

    if (ui->grYear->value() != 0)
    {
        whereGroup->append("Год обучения");
        whereGroup->append(ui->grYear->text());
        useTeach = true;
    }

    // ---------------------------------------------------------------
    // ---------------------- Объединение ----------------------------
    // ---------------------------------------------------------------

    if(ui->assName_ch->isChecked())
    {
        fromAss->append("Название");
        useAss = true;
    }

    if(ui->assOtd_ch->isChecked())
    {
        fromAss->append("Отдел");
        useAss = true;
    }

    if(ui->assDirect_ch->isChecked())
    {
        fromAss->append("Направленность");
        useAss = true;
    }

    // ---------------------------------------------------------------

    if (ui->assName->isModified())
    {
        QString str = ui->assName->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereAss->append("Название");
            whereAss->append(str);
            useTeach = true;
        }
    }

    if (ui->assOtd->isModified())
    {
        QString str = ui->assOtd->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereAss->append("Отдел");
            whereAss->append(str);
            useTeach = true;
        }
    }

    if (ui->assDirect->isModified())
    {
        QString str = ui->assDirect->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereAss->append("Направленность");
            whereAss->append(str);
            useTeach = true;
        }
    }

    // ---------------------------------------------------------------
    // ------------------------- Учащийся ----------------------------
    // ---------------------------------------------------------------

    if (ui->studName_ch->isChecked())
    {
        fromStud->append("Имя");
        useStud = true;
    }

    if (ui->studName->isModified())
    {
        QString str = ui->studName->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Имя");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studSurname_ch->isChecked())
    {
        fromStud->append("Фамилия");
        useStud = true;
    }

    if (ui->studSurname->isModified())
    {
        QString str = ui->studSurname->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Фамилия");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studPatr_ch->isChecked())
    {
        fromStud->append("Отчество");
        useStud = true;
    }

    if (ui->studPatr->isModified())
    {
        QString str = ui->studPatr->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Отчество");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studAdr_ch->isChecked())
    {
        fromStud->append("Адрес");
        useStud = true;
    }

    if (ui->studAdr->isModified())
    {
        QString str = ui->studAdr->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Адрес");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studBYear_ch->isChecked())
    {
        fromStud->append("Год рождения");
        useStud = true;
    }

   /* if (ui->studBYear->isModified())
    {
        QString str = ui->studBYear->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Год рождения");
            whereStud->append(str);
            useTeach = true;
        }
    } */

    if (ui->studClass_ch->isChecked())
    {
        fromStud->append("Класс");
        useStud = true;
    }

    if (ui->studClass->isModified())
    {
        QString str = ui->studClass->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Класс");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studDataIn_ch->isChecked())
    {
        fromStud->append("Дата заявления");
        useStud = true;
    }

   /* if (ui->studDataIn->isModified())
    {
        QString str = ui->studDataIn->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Дата заявления");
            whereStud->append(str);
            useTeach = true;
        }
    } */

    if (ui->studDataOut_ch->isChecked())
    {
        fromStud->append("Когда выбыл");
        useStud = true;
    }

   /* if (ui->studDataOut->isModified())
    {
        QString str = ui->studDataOut->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Когда выбыл");
            whereStud->append(str);
            useTeach = true;
        }
    } */

    if (ui->studDocNum_ch->isChecked())
    {
        fromStud->append("Номер документа");
        useStud = true;
    }

    if (ui->studDocNum->isModified())
    {
        QString str = ui->studDocNum->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Номер документа");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studDocType_ch->isChecked())
    {
        fromStud->append("Тип документа");
        useStud = true;
    }

    if (ui->studDocType->currentIndex() != 0)
    {
        QString str = ui->studDocType->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("Тип документа");
            whereStud->append(str);
            useTeach = true;
        }
    }


    if (ui->studEduForm_ch->isChecked())
    {
        fromStud->append("Форма обучения");
        useStud = true;
    }

    if (ui->studEduForm->currentIndex() != 0)
    {
        QString str = ui->studEduForm->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("Форма обучения");
            whereStud->append(str);
            useTeach = true;
        }
    }


    if (ui->studGender_ch->isChecked())
    {
        fromStud->append("Пол");
        useStud = true;
    }

    if (ui->studGender->currentIndex() != 0)
    {
        QString str = ui->studGender->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("Пол");
            whereStud->append(str);
            useTeach = true;
        }
    }


    if (ui->studIncom_ch->isChecked())
    {
        fromStud->append("Неполная семья");
        useStud = true;
    }

    if (ui->studIncom->currentIndex() != 0)
    {
        QString str = ui->studIncom->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("Неполная семья");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studInv_ch->isChecked())
    {
        fromStud->append("Инвалид");
        useStud = true;
    }

    if (ui->studInv->currentIndex() != 0)
    {
        QString str = ui->studInv->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("Инвалид");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studLarge_ch->isChecked())
    {
        fromStud->append("Многодетная семья");
        useStud = true;
    }

    if (ui->studLarge->currentIndex() != 0)
    {
        QString str = ui->studLarge->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("Многодетная семья");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studMail_ch->isChecked())
    {
        fromStud->append("e-mail");
        useStud = true;
    }

    if (ui->studMail->isModified())
    {
        QString str = ui->studMail->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("e-mail");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studMigrants_ch->isChecked())
    {
        fromStud->append("Мигранты");
        useStud = true;
    }

    if (ui->studMigrants->currentIndex() != 0)
    {
        QString str = ui->studMigrants->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("Мигранты");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studNeedy_ch->isChecked())
    {
        fromStud->append("Малообеспеченная семья");
        useStud = true;
    }

    if (ui->studNeedy->currentIndex() != 0)
    {
        QString str = ui->studNeedy->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("Малообеспеченная семья");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studOrph_ch->isChecked())
    {
        fromStud->append("Сирота");
        useStud = true;
    }

    if (ui->studOrph->currentIndex() != 0)
    {
        QString str = ui->studOrph->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("Сирота");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studParents_ch->isChecked())
    {
        fromStud->append("Родители");
        useStud = true;
    }

    if (ui->studParents->isModified())
    {
        QString str = ui->studParents->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Родители");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studPhone_ch->isChecked())
    {
        fromStud->append("Телефон");
        useStud = true;
    }

    if (ui->studPhone->isModified())
    {
        QString str = ui->studPhone->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Телефон");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studPolice_ch->isChecked())
    {
        fromStud->append("На учёте в полиции");
        useStud = true;
    }

    if (ui->studPolice->currentIndex() != 0)
    {
        QString str = ui->studPolice->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("На учёте в полиции");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studSchoolReg_ch->isChecked())
    {
        fromStud->append("Район школы");
        useStud = true;
    }

    if (ui->studSchoolReg->isModified())
    {
        QString str = ui->studSchoolReg->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Район школы");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studSchool_ch->isChecked())
    {
        fromStud->append("Школа");
        useStud = true;
    }

    if (ui->studSchool->isModified())
    {
        QString str = ui->studSchool->text().simplified().replace(QRegularExpression("-{2,}"), "-");
        if (!str.isEmpty())
        {
            whereStud->append("Школа");
            whereStud->append(str);
            useTeach = true;
        }
    }

    if (ui->studWhealth_ch->isChecked())
    {
        fromStud->append("С ослабленным здоровьем");
        useStud = true;
    }

    if (ui->studWhealth->currentIndex() != 0)
    {
        QString str = ui->studWhealth->currentText();
        if (!str.isEmpty())
        {
            whereStud->append("С ослабленным здоровьем");
            whereStud->append(str);
            useTeach = true;
        }
    }

    // ---------------------------------------------------------------


    if (useTeach)
    {
        from->append(" Преподаватели,");

        for (QString & str : *fromTeach)
        {
            columns->append(" Преподаватели.`" + str + "`,");
        }
    }

    if (useStud)
    {
        from->append(" Учащиеся,");

        for (QString & str : *fromStud)
        {
            columns->append(" Учащиеся.`" + str + "`,");
        }
    }

    if (useAss)
    {
        from->append(" Объединения, Направленности,");
        where->append(" Направленности.`ID` = Объединения.`ID Направленности`,");
    }

    if (useGroup)
    {
        from->append(" Группы,");
        if (useTeach)
        {
            where->append(" Преподаватели.`ID` = Группы.`ID Преподавателя`,");
        }

        if (useStud)
        {
            from->append(" Нагрузка,");
            where->append(" Учащиеся.`ID` = Нагрузка.`ID учащегося`, Группы.`ID` = Нагрузка.`ID группы`,");
        }

    }




    // Убираем запятую в конце FROM
    from->resize(from->size()-1);
    // Убираем запятую в конце WHERE
    where->resize(where->size()-1);

    query->append("SELECT" + *columns + " FROM" + *from + " WHERE" + *where + ";");
    signalQuery(*query);

}
