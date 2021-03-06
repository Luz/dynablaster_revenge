#pragma once

// framework
#include "math/vector2.h"
#include "math/vector.h"

// Qt
#include <QList>


class LensFlareGhost
{
   public:

      LensFlareGhost();


      float getSize() const;
      void setSize(float size);

      float getRayPosition() const;
      void setRayPosition(float scalar);

      float getOffsetY() const;
      void setOffsetY(float value);

      int getTileRow() const;
      void setTileRow(int value);

      int getTileColumn() const;
      void setTileColumn(int value);

      Vector getColor() const;
      void setColor(const Vector &value);

      //! getter for width
      int getWidth() const;

      //! setter for width
      void setWidth(int value);

      //! getter for height
      int getHeight() const;

      //! setter for height
      void setHeight(int value);

      static QList<LensFlareGhost> readGhostStrip(const QString& fileName);

      //! getter for angle
      float getAngle() const;

      //! setter for angle
      void setAngle(float value);

      //! getter for speed
      float getSpeed() const;

      //! setter for speed
      void setSpeed(float value);


   protected:

      // read from config
      float mSize;
      float mRayPosition;
      float mOffsetY;
      int mTileRow;
      int mTileColumn;
      Vector mColor;
      int mWidth;
      int mHeight;
      float mAngle;
      float mSpeed;
};

