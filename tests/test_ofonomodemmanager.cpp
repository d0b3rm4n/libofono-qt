/*
 * This file is part of ofono-qt
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Alexander Kanavin <alexander.kanavin@nokia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#include <QtTest/QtTest>
#include <QtCore/QObject>

#include <ofonomodemmanager.h>
#include <ofonomodem.h>

#include <QtDebug>


class TestOfonoModemManager : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
	mm = new OfonoModemManager(this);
    }

    void testOfonoModemManager()
    {
        QVERIFY(mm->modems().contains("/phonesim") == true);
    }

    void testOfonoModemManagerAddRemove()
    {
        QSignalSpy add(mm, SIGNAL(modemAdded(const QString &)));
        QSignalSpy remove(mm, SIGNAL(modemRemoved(const QString &)));
        qDebug() << "Please stop oFono and then start it again";
	for (int i=0; i<30; i++) {
	    if (add.count() > 0 && remove.count() > 0)
	        break;
	    QTest::qWait(1000);
	}
        QVERIFY(mm->modems().contains("/phonesim") == true);
        OfonoModem *m = new OfonoModem(OfonoModem::ManualSelect, "/phonesim", this);
        m->setPowered(true);
        QTest::qWait(5000);
        m->setOnline(true);
        QTest::qWait(5000);
        QVERIFY(remove.count() > 0);
	QVERIFY(add.count() > 0);
    }    

    void cleanupTestCase()
    {

    }


private:
    OfonoModemManager *mm;
};

QTEST_MAIN(TestOfonoModemManager)
#include "test_ofonomodemmanager.moc"
