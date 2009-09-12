#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QString>
#include <QTextCharFormat>
#include <QColor>
#include <QFont>
#include <QList>
#include <QTextLayout>

class TextEdit;
class TextLayout;
class TextDocument;
class SyntaxHighlighter : public QObject
{
    Q_OBJECT
public:
    SyntaxHighlighter(QObject *parent = 0);
    SyntaxHighlighter(TextEdit *parent);
    ~SyntaxHighlighter();
    void setTextEdit(TextEdit *doc);
    TextEdit *textEdit() const;
    TextDocument *document() const;
public Q_SLOTS:
    void rehighlight();
protected:
    virtual void highlightBlock(const QString &text) = 0;
    QString currentBlock() const { return d->currentBlock; }
    void setFormat(int start, int count, const QTextCharFormat &format);
    void setFormat(int start, int count, const QColor &color);
    void setFormat(int start, int count, const QFont &font);
    void setBlockFormat(const QTextBlockFormat &format);
    QTextCharFormat format(int pos) const;
    int previousBlockState() const;
    int currentBlockState() const;
    void setCurrentBlockState(int s);
    int currentBlockPosition() const;
private:
    struct Private {
        Private() : textEdit(0), textLayout(0), previousBlockState(0), currentBlockState(0),
                    currentBlockPosition(-1) {}
        TextEdit *textEdit;
        TextLayout *textLayout;
        int previousBlockState, currentBlockState, currentBlockPosition;
        QList<QTextLayout::FormatRange> formatRanges;
        QTextBlockFormat blockFormat;
        QString currentBlock;
    } *d;

    friend class TextEdit;
    friend class TextLayout;
};

#endif
