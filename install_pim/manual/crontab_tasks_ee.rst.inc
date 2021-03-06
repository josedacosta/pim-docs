Configuring tasks via crontab
-----------------------------

The application needs the following tasks to be executed in background on a regular basis. The frequency has to be adapted according to your data volume.

Edit your crontab with ``crontab -e`` and configure your tasks.

.. warning::

    Be sure to update the cron of the user used to install the PIM, to be able to run the command

You have to add these 6 commands to your local installation:

.. code-block:: bash
    :linenos:

    php /path/to/installation/pim-enterprise-standard/bin/console pim:completeness:calculate --env=prod                                         # recalculates the products completeness
    php /path/to/installation/pim-enterprise-standard/bin/console pim:versioning:refresh --env=prod                                             # processes pending versions
    php /path/to/installation/pim-enterprise-standard/bin/console akeneo:rule:run --env=prod                                                    # executes rules on products
    php /path/to/installation/pim-enterprise-standard/bin/console pimee:project:notify-before-due-date --env=prod                               # check and send notifications (TeamWork Assistant)
    php /path/to/installation/pim-enterprise-standard/bin/console pim:asset:send-expiration-notification --env=prod                             # check and send notifications for asset date delay
    php /path/to/installation/pim-enterprise-standard/bin/console pimee:project:recalculate --env=prod                                          # recalculate project completeness (TeamWork Assistant)
    php /path/to/installation/pim-enterprise-standard/bin/console akeneo:batch:publish-job-to-queue franklin_insights_fetch_products --env=prod # fetch suggested data for products subscribed to Franklin Insights

.. note::
   **Note:** ``franklin_insights_fetch_products`` batch job is to be set only if you activate Franklin Insights EE feature.


In the following example, these lines will run the completeness calculation at 11pm, the versioning calculation at 5am, the rules calculation at 6pm and the aggregate volume at 10pm every day:

.. code-block:: bash
    :linenos:

    # m  h  dom  mon  dow  command
    0 23  *    *    *    php /path/to/installation/pim-enterprise-standard/bin/console pim:completeness:calculate --env=prod > /path/to/installation/pim-enterprise-standard/var/logs/calculate_completeness.log 2>&1
    0 5   *    *    *    php /path/to/installation/pim-enterprise-standard/bin/console pim:versioning:refresh --env=prod > /path/to/installation/pim-enterprise-standard/var/logs/refresh_versioning.log 2>&1
    0 18  *    *    *    php /path/to/installation/pim-enterprise-standard/bin/console akeneo:rule:run --env=prod > /path/to/installation/pim-enterprise-standard/var/logs/rule_run.log 2>&1
    0 22  *    *    *    php /path/to/installation/pim-enterprise-standard/bin/console pim:volume:aggregate --env=prod > /path/to/installation/pim-enterprise-standard/var/logs/volume_aggregate.log 2>&1

.. note::

    ``> /path/to/installation/pim-enterprise-standard/var/logs/calculate_completeness.log 2>&1`` is to redirect both stdout and stderr to your log file.

.. note::

    The completeness is already recalculated automatically after an import, a mass action, after the rules are executed, after a family edition and after a product is saved.

.. warning::

    Since some tasks may take a long time to be executed, adapt the frequency of these tasks according to your needs, to your server capabilities and to your catalog size.
